#include "matchmaking.hpp"
// ====== Loby class ======





// ====== GameCandidate class ======

GameCandidate::GameCandidate(RequestJoinGame joinGame) 
:  numberOfPlayersMax_{(joinGame.bindGame.gameMode == GameMode::Dual) ? numberOfPlayersMax_ = 2 :numberOfPlayersMax_ = 9 }, gameMode{joinGame.bindGame.gameMode} {
}

GameCandidate::GameCandidate(RequestCreateGame createGame) : numberOfPlayersMax_{createGame.bindCreateGame.targetNumPlayers}, gameMode{createGame.bindCreateGame.gameMode} {

}

bool GameCandidate::tryToAddPlayer(RequestJoinGame joinGame ){
    if (isThereRoomInThisGame()){
        players_.push_back(joinGame.playerId);
        numberOfPlayersMax_ ++;
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

// ======= matchmaking class =======


void Matchmaking::addPlayer(RequestJoinGame joinGame){
    findaGame(getGame(joinGame.bindGame.gameMode), joinGame);
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

void Matchmaking::findaGame(std::vector<GameCandidate>& games, RequestJoinGame joinGame){
    bool joinFriend = joinGame.bindGame.friendId.has_value();
    int size = games.size(), idx = 0;
    bool findGame = false;
    while (idx < size && !findGame){
        if (joinFriend){
            if (games[idx].isthisPlayerInThisGame(joinGame.bindGame.friendId.value())){
                findGame = games[idx].tryToAddPlayer(joinGame);
            }
        }else {
            findGame = games[idx].tryToAddPlayer(joinGame);
        }
        if (games[idx].isThisPartyReady()){
            //create a game from gameCandidate
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