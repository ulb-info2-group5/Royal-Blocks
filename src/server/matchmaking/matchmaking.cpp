#include "matchmaking.hpp"
// ====== Loby class ======





// ====== GameCandidate class ======

GameCandidate::GameCandidate(NumberOfPlayers numberOfPlayersMax) : numberOfPlayersMax_{numberOfPlayersMax}, numberOfPlayerTotale_{0} {

}




// ======= matchmaking class =======


void Matchmaking::addPlayer(bindings::JoinGame joinGame){
    findaGame(getGame(joinGame.gameMode), joinGame);
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

void Matchmaking::findaGame(std::vector<GameCandidate>& games, bindings::JoinGame joinGame){
    bool joinFriend = joinGame.friendId.has_value();
    int size = games.size(), idx = 0;
    bool findGame = false;
    while (idx < size && !findGame){
        if (joinFriend){
            if (games[idx].isthisPlayerInThisGame(joinGame.friendId.value())){
                games[idx].tryToAddPlayer(joinGame);
            }
        }else {
            games[idx].tryToAddPlayer(joinGame);
        }
        if (games[idx].isThisPartyReady()){
            //create a game from gameCandidate
        }
    }
    if (!findGame) createNewGameCandidate(joinGame);
}

void Matchmaking::createNewGameCandidate(bindings::JoinGame joinGame){
    
    if (joinGame.gameMode == GameMode::Dual){
        //getGame(GameMode::Dual).push_back(GameCandidate{2})
    }else {

    }
}


void Matchmaking::createAGame(bindings::CreateGame createGame){

}