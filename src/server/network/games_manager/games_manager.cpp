#include "games_manager.hpp"



// ======== private methode ========
void GamesManager::deleteGame(GameID gameId){
    //TODO : update clientTOGame_ , gameThreads and gameSessions 
    //to avoid storing the finished games 
}


// ======== public methode ========

GamesManager::GamesManager(UpdateGameStates updateGameStates) :updateGameStates_(updateGameStates) {}


void GamesManager::startGameServeur(GameMode gameMode, std::vector<PlayerID> playerIds ){
    for (PlayerID id : playerIds){
        std::cout << " id : " << id << std::endl;
        clientToGame_[id] = nextGameId;
    }
    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>(gameMode , std::move(playerIds),updateGameStates_, nextGameId, 
        [this](GameID gameId) {callBackFinishGame(gameId); }); 
    gameSessions_[nextGameId] = gameServer;
    gamethreads_[nextGameId] = std::thread([gameServer]() {gameServer->run(); });
    std::cout << " ==<< create a new game >>== gameServer id : " << nextGameId << std::endl; 
    nextGameId += 1;
}

void GamesManager::enqueueGameBinding(int clientId, const std::string& strBindings){
    GameID gameId = clientToGame_[clientId];
    auto gameServer = gameSessions_[gameId]; 
    boost::asio::post(gameServer->getIoContext(), [gameServer, clientId, strBindings](){
        gameServer->enqueueBinding(clientId, strBindings);
    });
    std::cout << "player id : " << clientId << " game id : " << gameId << " add : " << strBindings << std::endl;
}



void GamesManager::callBackFinishGame(GameID gameId ){
    
    // TODO :  for all clients who participated -> send the game score  
    deleteGame(gameId);
}


bool GamesManager::isThisClientInGame(PlayerID playerId){
    bool res =  clientToGame_.find(playerId) != clientToGame_.end();
    std::cout <<  res << std::endl;
    return res;
}