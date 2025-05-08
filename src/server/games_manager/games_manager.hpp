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

/**
 * @class
 *
 * @brief
 */
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
    
    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void joinerThreadFunc();

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void notifyGameFinished(int gameID);
    

  public:
    GamesManager( SaveScoreCallback saveScoreCallback, UpdateRankingCallback updateRankingCallback);
    ~GamesManager();
    
    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void shutdown();

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void makeClientJoinGame(std::shared_ptr<ClientLink> clientLink, std::shared_ptr<GameServer> gameServer);


    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void enqueueGameBinding(const std::shared_ptr<ClientLink>& clientLink, const std::string &strBindings);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    std::shared_ptr<GameServer> startGameServeur(GameMode gameMode, std::vector<Player> players);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void callBackFinishGame(GameID gameId);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void joinGameAsViewer(const std::shared_ptr<ClientLink> viewerLink, const std::shared_ptr<ClientLink> friendLink);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void quiGameAsViewer(const std::shared_ptr<ClientLink>& viewerLink);
};

#endif