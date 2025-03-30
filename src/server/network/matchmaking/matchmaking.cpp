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
    : numberOfPlayerTotale_{0}, numberOfPlayersMax_{createGame.bindCreateGame.targetNumPlayers},
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

bool GameCandidate::isThereRoomInThisGame() {
    return numberOfPlayerTotale_ < numberOfPlayersMax_;
}

bool GameCandidate::isThisPartyReady() {
    return numberOfPlayersMax_ == numberOfPlayerTotale_;
}

bool GameCandidate::isthisPlayerInThisGame(UserID userId) {
    for (auto player : players_) {
        if (userId == player.userID) return true;
    }
    return false;
}

std::vector<Player> &GameCandidate::getPlayers() { return players_; }

std::vector<UserID> GameCandidate::getPlayerIDs(){
    std::vector<UserID> userIds;
    for (auto player : players_){
        userIds.push_back(player.userID);
    }
    return userIds;
}


GameMode GameCandidate::getGameMode() { return gameMode; }

// ======= matchmaking class =======


void Matchmaking::addPlayer(RequestJoinGame joinGame, GamesManager &gamesManager) {
    if (joinGame.bindGame.gameMode == GameMode::Endless) {
        std::vector<UserID> players;
        players.emplace_back(joinGame.player.userID);
        gameFindCallback_(players, gamesManager.startGameServeur(GameMode::Endless, std::vector<Player>{joinGame.player}));
        return;
    }

    findaGame(getGame(joinGame.bindGame.gameMode), joinGame, gamesManager);
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
                            RequestJoinGame joinGame,
                            GamesManager &gamesManager) {
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
            
            startGame(std::move(*it), gamesManager);
            it = games.erase(it);
        } else {
            ++it;
        }
    }
    if (!findGame) createNewGameCandidate(games, joinGame);
}

Matchmaking::Matchmaking(GameFindCallback gameFindCallback) : gameFindCallback_(gameFindCallback) {

}


void Matchmaking::createNewGameCandidate(std::vector<GameCandidate> &games,
                                         RequestJoinGame joinGame) {
    games.push_back(GameCandidate{joinGame});
}

void Matchmaking::createAGame(RequestCreateGame createGame) {
    getGame(createGame.bindCreateGame.gameMode)
        .push_back(GameCandidate{createGame});
}

void Matchmaking::startGame(GameCandidate &&gameCandidate,GamesManager &gamesManager) {
    gameFindCallback_(gameCandidate.getPlayerIDs(), 
    gamesManager.startGameServeur(gameCandidate.getGameMode(),gameCandidate.getPlayers()) );
    
}
