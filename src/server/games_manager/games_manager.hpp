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
 *@class GameServer 
 *
 *@brief manages all current games 
 *
 **/
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
    // thread that will join a game thread when the game is finished
    std::thread joinerThread_;
    GameID nextGameId = 1;
    
    /**
    * @brief launched by joinerThread will wait for join finished game  
    */
    void joinerThreadFunc();

    /**
    * @brief notify the joinerThread that the game is finish
    */
    void notifyGameFinished(int gameID);
    

  public:
    GamesManager( SaveScoreCallback saveScoreCallback, UpdateRankingCallback updateRankingCallback);
    ~GamesManager();
    
    /**
    * @brief shutdown the gamesManager join all game Threads and join the joinerThread 
    */
    void shutdown();

    /**
    * @brief update the user State and give a gameServer weak_ptr to the client  
    */
    void makeClientJoinGame(std::shared_ptr<ClientLink> clientLink, std::shared_ptr<GameServer> gameServer);


    /**
    * @brief enqueue gameBinding
    */
    void enqueueGameBinding(const std::shared_ptr<ClientLink>& clientLink, const std::string &strBindings);

    /**
    * @brief start game : create a new thread that will run the game 
    */
    std::shared_ptr<GameServer> startGameServeur(GameMode gameMode, std::vector<Player> players);

    /**
    * @brief callback to notify that the game is finish send by the gameServer
    */
    void callBackFinishGame(GameID gameId);

    /**
    * @brief joins client to a game as viewer   
    *
    */
    void joinGameAsViewer(const std::shared_ptr<ClientLink> viewerLink, const std::shared_ptr<ClientLink> friendLink);

    /**
    * @brief quit game as viewer 
    */
    void quiGameAsViewer(const std::shared_ptr<ClientLink>& viewerLink);
};

#endif