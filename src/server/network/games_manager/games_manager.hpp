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
// TODO : rename to sendGameState 
using UpdateGameStates = std::function<void (PlayerID, nlohmann::json)>;

class GamesManager {
    
    private:
        std::unordered_map<PlayerID , GameID > clientToGame_;
        std::unordered_map<GameID , std::shared_ptr<GameServer> > gameSessions_;
        std::unordered_map<GameID , std::thread> gamethreads_; 

        UpdateGameStates updateGameStates_;
        GameID nextGameId = 1;

        void deleteGame(GameID gameId);
    public: 
        GamesManager(UpdateGameStates updateGameStates);
        void enqueueGameBinding(int clientId, const std::string& strBindings);
        void startGameServeur(GameMode gameMode, std::vector<PlayerID> playerIds );

        void callBackFinishGame(GameID gameId);

};

#endif 