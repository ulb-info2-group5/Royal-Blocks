#ifndef GAMES_MANAGER_HPP
#define GAMES_MANAGER_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <condition_variable>
#include <atomic>

#include "../game_server/game_server.hpp"

using SaveScoreCallback = std::function<void(UserID, int)>;
using UpdateRankingCallback = std::function<void()>;

class GamesManager {

  private:
    std::unordered_map<GameID, std::shared_ptr<GameServer>> gameSessions_;
    std::unordered_map<GameID, std::thread> gamethreads_;
    std::mutex mutex;
    std::condition_variable cv;

    std::queue<GameID> finishedGames_;

    SaveScoreCallback saveScoreCallback_;
    UpdateRankingCallback updateRankingCallback_;
    std::atomic<bool> running = true;
    std::thread joinerThread_;
    GameID nextGameId = 1;
    
    void joinerThreadFunc();

    void notifyGameFinished(int gameID);
    

  public:
    GamesManager( SaveScoreCallback saveScoreCallback, UpdateRankingCallback updateRankingCallback);
    ~GamesManager();
    
    void shutdown();
    void makeClientJoinGame(std::shared_ptr<ClientLink> clientLink, std::shared_ptr<GameServer> gameServer);

    void enqueueGameBinding(const std::shared_ptr<ClientLink>& clientLink, const std::string &strBindings);
    std::shared_ptr<GameServer> startGameServeur(GameMode gameMode, std::vector<Player> players);
    void callBackFinishGame(GameID gameId);

    void joinGameAsViewer(const std::shared_ptr<ClientLink> viewerLink, const std::shared_ptr<ClientLink> friendLink);

    void quiGameAsViewer(const std::shared_ptr<ClientLink>& viewerLink);
};

#endif