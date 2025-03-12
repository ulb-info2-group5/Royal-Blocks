#include "matchmaking.hpp"
// ====== Loby class ======





// ====== GameCandidate class ======

GameCandidate::GameCandidate(RequestJoinGame joinGame) 
:  numberOfPlayersMax_{(joinGame.bindGame.gameMode == GameMode::Dual) ?  MAXPLAYERDUAL : MAXPLAYERCLASSICANDROYAL }, gameMode{joinGame.bindGame.gameMode} {
    std::cout << "gameCandidate create (RequestJoinGame)" << std::endl;
    numberOfPlayerTotale_ ++;
    players_.push_back(joinGame.playerId);
}

GameCandidate::GameCandidate(RequestCreateGame createGame) : numberOfPlayersMax_{createGame.bindCreateGame.targetNumPlayers}, gameMode{createGame.bindCreateGame.gameMode} {
    std::cout << "gameCandidate create (RequestCreateGame)" << std::endl;
    numberOfPlayerTotale_ ++;
    players_.push_back(createGame.playerId);
}

bool GameCandidate::tryToAddPlayer(RequestJoinGame joinGame ){
    if (isThereRoomInThisGame()){
        players_.push_back(joinGame.playerId);
        numberOfPlayerTotale_ ++;
        std::cout << "add player " << std::endl;
        return true;
    }
    return false;
}

bool GameCandidate::isThereRoomInThisGame(){
    return numberOfPlayerTotale_ < numberOfPlayersMax_;
}


bool GameCandidate::isThisPartyReady(){
    return numberOfPlayersMax_ == numberOfPlayerTotale_;
}


bool GameCandidate::isthisPlayerInThisGame(PlayerID playerId){
    for (auto id : players_){
        if (id == playerId) return true;
    }
    return false;
}


std::vector<PlayerID>& GameCandidate::getPlayers(){
    return players_;
}

GameMode GameCandidate::getGameMode(){
    return gameMode;
}

// ======= matchmaking class =======


void Matchmaking::addPlayer(RequestJoinGame joinGame, GamesManager& gamesManager){
    findaGame(getGame(joinGame.bindGame.gameMode), joinGame, gamesManager);
}

std::vector<GameCandidate>& Matchmaking::getGame(GameMode gameMode){
    switch (gameMode)
    {
    case GameMode::Classic:
        return gamesCanditatesClassic_;
        
    case GameMode::Dual:
        return gamesCanditatesDuel_;
        
    case GameMode::RoyalCompetition:
        return gamesCanditatesRoyalCompetition_;
        
    default:
        std::cerr << "incorect gamesMode" << std::endl;
        break;
    }
}

void Matchmaking::findaGame(std::vector<GameCandidate>& games, RequestJoinGame joinGame, GamesManager& gamesManager){
    bool joinFriend = joinGame.bindGame.friendId.has_value(), findGame = false;
    auto it = games.begin();
    while (it != games.end() && !findGame){
        if (joinFriend){
            if (it->isthisPlayerInThisGame(joinGame.bindGame.friendId.value())){
                findGame = it->tryToAddPlayer(joinGame);
            }
        }else {
            findGame = it->tryToAddPlayer(joinGame);
        }
        if (it->isThisPartyReady()){
            std::cout << "game ready" << std::endl;
            startGame(std::move(*it), gamesManager);
            it = games.erase(it);
        }else {
            ++it;
        }
    }
    if (!findGame) createNewGameCandidate(games, joinGame);
}

void Matchmaking::createNewGameCandidate(std::vector<GameCandidate>& games, RequestJoinGame joinGame){
    games.push_back(GameCandidate{joinGame});
}


void Matchmaking::createAGame(RequestCreateGame createGame){
    getGame(createGame.bindCreateGame.gameMode).push_back(GameCandidate{createGame});
}

void Matchmaking::startGame(GameCandidate &&gameCandidate, GamesManager& gamesManager){
    gamesManager.startGameServeur(gameCandidate.getGameMode(), gameCandidate.getPlayers());
}