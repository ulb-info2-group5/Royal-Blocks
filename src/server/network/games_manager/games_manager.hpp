#ifndef GAMES_MANAGER_HPP
#define GAMES_MANAGER_HPP


#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <thread>
#include <memory>

#include "../../game_server/game_server.hpp"

using UpdateGameStates = std::function<void (PlayerID, nlohmann::json)>;

class GamesManager {
    
    private:
        std::unordered_map<PlayerID , int > clientToGame_;
        std::unordered_map<int , std::shared_ptr<GameServer> > gameSessions_;
        std::unordered_map<int , std::thread> gamethreads_; 

        UpdateGameStates updateGameStates_;
        int nextGameId = 1;

        void stopGame(int gameId);
    public: 
        GamesManager(UpdateGameStates updateGameStates);
        void enqueueGameBinding(int clientId, const std::string& strBindings);
        void startGameServeur(GameMode gameMode, std::vector<PlayerID> playerIds );

};

#endif 