#include "games_manager.hpp"



// ======== private methode ========



// ======== public methode ========

GamesManager::GamesManager(UpdateGameStates updateGameStates) :updateGameStates_(updateGameStates) {}


void GamesManager::startGameServeur(GameMode gameMode, std::vector<PlayerID> playerIds ){
    for (PlayerID id : playerIds){
        clientToGame_[id] = nextGameId;
    }
    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>(gameMode , std::move(playerIds), updateGameStates_); 
    gameSessions_[nextGameId] = gameServer;
    gamethreads_[nextGameId] = std::thread([gameServer]() {gameServer->run(); });
    std::cout << " ==<< create a new game >>== gameServer id : " << nextGameId << std::endl; 
    nextGameId += 1;
}

void GamesManager::enqueueGameBinding(int clientId, const std::string& strBindings){

    int gameId = clientToGame_[clientId];
    auto gameServer = gameSessions_[gameId]; 
    boost::asio::post(gameServer->getIoContext(), [gameServer, clientId, strBindings](){
        gameServer->enqueueBinding(clientId, strBindings);
    });
    std::cout << "player id : " << clientId << " game id : " << gameId << " add : " << strBindings << std::endl;
}

