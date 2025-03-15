#ifndef GAMES_MANAGER_HPP
#define GAMES_MANAGER_HPP

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../../game_server/game_server.hpp"

// TODO : rename to sendGameState
using UpdateGamePlayer = std::function<void(UserID, nlohmann::json)>;
using SaveScoreCallback = std::function<void(UserID, int)>;

class GamesManager {

  private:
    std::unordered_map<UserID, GameID> clientToGame_;
    std::unordered_map<GameID, std::shared_ptr<GameServer>> gameSessions_;
    std::unordered_map<GameID, std::thread> gamethreads_;

    UpdateGamePlayer updateGamePlayer_;
    SaveScoreCallback saveScoreCallback_;
    GameID nextGameId = 1;

    void deleteGame(GameID gameId);

  public:
  GamesManager(UpdateGamePlayer updateGamePlayer, SaveScoreCallback saveScoreCallback);

    void enqueueGameBinding(int clientId, const std::string &strBindings);
    void startGameServeur(GameMode gameMode, std::vector<Player> players);
    void callBackFinishGame(GameID gameId);
    bool isThisClientInGame(UserID userId);
};

#endif