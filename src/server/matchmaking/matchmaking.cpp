/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "matchmaking.hpp"
#include <vector>
// ====== Loby class ======

// ====== GameCandidate class ======

GameCandidate::GameCandidate(RequestJoinGame joinGame)
    : numberOfPlayerTotale_{0},
      numberOfPlayersMax_{(joinGame.bindGame.gameMode == GameMode::Dual)
                              ? MAXPLAYERDUAL
                              : MAXPLAYERCLASSICANDROYAL},
      gameMode{joinGame.bindGame.gameMode} {
    std::cout << "gameCandidate create (RequestJoinGame)" << std::endl;
    numberOfPlayerTotale_++;
    players_.push_back(joinGame.player);
}

GameCandidate::GameCandidate(RequestCreateGame createGame)
    : numberOfPlayerTotale_{0},
      numberOfPlayersMax_{createGame.bindCreateGame.targetNumPlayers},
      gameMode{createGame.bindCreateGame.gameMode} {
    std::cout << "gameCandidate create (RequestCreateGame)" << std::endl;
    numberOfPlayerTotale_++;
    players_.push_back(createGame.player);
}

bool GameCandidate::tryToAddPlayer(RequestJoinGame joinGame) {
    if (isThereRoomInThisGame()) {
        players_.push_back(joinGame.player);
        numberOfPlayerTotale_++;
        std::cout << "add player " << std::endl;
        return true;
    }
    return false;
}

void GameCandidate::removePlayer(UserID playerID) {
    auto it = players_.begin();
    while (it != players_.end()) {
        if (it->userID == playerID) {
            std::cout << "delete client " << std::endl;
            players_.erase(it);
            numberOfPlayerTotale_--;
            std::cout << numberOfPlayerTotale_ << std::endl;
            return;
        } else {
            it++;
        }
    }
}

bool GameCandidate::isThereRoomInThisGame() {
    return numberOfPlayerTotale_ < numberOfPlayersMax_;
}

bool GameCandidate::isThisPartyReady() {
    return numberOfPlayersMax_ == numberOfPlayerTotale_;
}
bool GameCandidate::isEmpty() { return numberOfPlayerTotale_ == 0; }

bool GameCandidate::isthisPlayerInThisGame(UserID userId) {
    for (auto player : players_) {
        if (userId == player.userID) return true;
    }
    return false;
}

std::vector<Player> &GameCandidate::getPlayers() { return players_; }

std::vector<UserID> GameCandidate::getPlayerIDs() {
    std::vector<UserID> userIds;
    for (auto player : players_) {
        userIds.push_back(player.userID);
    }
    return userIds;
}

GameMode GameCandidate::getGameMode() { return gameMode; }

// ======= matchmaking class =======

void Matchmaking::addPlayer(RequestJoinGame joinGame) {
    if (joinGame.bindGame.gameMode == GameMode::Endless) {
        std::vector<Player> players;
        players.emplace_back(joinGame.player);
        gameFindCallback_(players, GameMode::Endless);
        return;
    }

    findaGame(getGame(joinGame.bindGame.gameMode), joinGame);
}

std::vector<GameCandidate> &Matchmaking::getGame(GameMode gameMode) {
    if (gameMode == GameMode::Classic) {
        return gamesCanditatesClassic_;
    }

    else if (gameMode == GameMode::Dual) {
        return gamesCanditatesDuel_;
    }

    else if (gameMode == GameMode::RoyalCompetition) {
        return gamesCanditatesRoyalCompetition_;
    }

    throw std::runtime_error("incorect gamesMode");
}

void Matchmaking::findaGame(std::vector<GameCandidate> &games,
                            RequestJoinGame joinGame) {
    bool joinFriend = joinGame.bindGame.friendId.has_value(), findGame = false;
    auto it = games.begin();
    while (it != games.end() && !findGame) {
        if (joinFriend) {
            if (it->isthisPlayerInThisGame(
                    joinGame.bindGame.friendId.value())) {
                findGame = it->tryToAddPlayer(joinGame);
            }
        } else {
            findGame = it->tryToAddPlayer(joinGame);
        }
        if (it->isThisPartyReady()) {
            std::cout << "game ready" << std::endl;

            startGame(std::move(*it));
            it = games.erase(it);
        } else {
            ++it;
        }
    }
    if (!findGame) createNewGameCandidate(games, joinGame);
}

Matchmaking::Matchmaking(GameFindCallback gameFindCallback)
    : gameFindCallback_(gameFindCallback) {}

void Matchmaking::createNewGameCandidate(std::vector<GameCandidate> &games,
                                         RequestJoinGame joinGame) {
    games.push_back(GameCandidate{joinGame});
}

void Matchmaking::createAGame(RequestCreateGame createGame) {
    getGame(createGame.bindCreateGame.gameMode)
        .push_back(GameCandidate{createGame});
}

void Matchmaking::removePlayer(UserID playerID, GameMode gameMode) {
    auto &gameList = getGame(gameMode);
    auto it = gameList.begin();
    while (it != gameList.end()) {
        if (it->isthisPlayerInThisGame(playerID)) {
            std::cout << "find client " << std::endl;
            it->removePlayer(playerID);
            if (it->isEmpty()) {
                gameList.erase(it);
            }
            return;
        } else {
            it++;
        }
    }
}

void Matchmaking::startGame(GameCandidate &&gameCandidate) {

    gameFindCallback_(gameCandidate.getPlayers(), gameCandidate.getGameMode());
}

void Matchmaking::abortMatchmaking(
    const std::shared_ptr<ClientLink> &clientLink) {
    if (clientLink->getUserState() != bindings::State::Matchmaking) {
        std::cerr << "Player not in Matchmaking " << std::endl;
    } else {
        removePlayer(clientLink->getUserID(),
                     clientLink->getGameMode().value());
        clientLink->setUserState(bindings::State::Menu);
    }
}
