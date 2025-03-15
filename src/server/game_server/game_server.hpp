#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/buy_bonus.hpp"
#include "../../common/bindings/in_game/buy_penalty.hpp"
#include "../../common/bindings/in_game/empty_penalty_stash.hpp"
#include "../../common/bindings/in_game/hold_next_tetromino.hpp"
#include "../../common/bindings/in_game/move_active.hpp"
#include "../../common/bindings/in_game/rotate_active.hpp"
#include "../../common/bindings/in_game/select_target.hpp"
#include "../../common/bindings/in_game/game_over.hpp"

#include "game_engine/game_engine.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <boost/asio.hpp>

using GameID = size_t;

using UpdateGamePlayer = std::function<void(UserID, nlohmann::json)>;
using CallBackFinishGame = std::function<void(GameID)>;

struct Player {
    UserID userID;
    std::string username;
};

class GameServer {

  private:
    boost::asio::io_context context_;
    boost::asio::steady_timer tickTimer_;
    GameStatePtr pGameState_;
    GameEngine engine;
    GameID gameId_;

    UpdateGamePlayer updateGamePlayer_;
    CallBackFinishGame callBackFinishGame_;

    /**
     * @brief Signals the engine that an engine tick occured. Resets the timer
     * for the next tick.
     */
    void onTimerTick();

  public:
    /**
     * @brief Constructor.
     */
    GameServer(GameMode gameMode, std::vector<Player> &&players,
              UpdateGamePlayer updateGamePlayer, GameID id,
              CallBackFinishGame callBackFinishGame);
    GameServer(const GameServer &) = delete;
    GameServer(GameServer &&) = delete;
    GameServer &operator=(const GameServer &) = delete;
    GameServer &operator=(GameServer &&) = delete;

    /**
     * @brief Enqueues a new binding as a string (json).
     */
    void enqueueBinding(UserID userId, const std::string &bindingStr);

    /**
     * @brief Sends the GameState to all the connected people in the game
     * include viewers. TODO: (not implemented yet)
     */
    void sendGameStates();

    /**
     * @brief Runs the server. This function returns as soon as the game is
     * finished.
     */
    void run();

    // === getters ===

    boost::asio::io_context &getIoContext();

    std::vector<UserID> getVectorPlayersId();
};

#endif // GAME_SERVER_HPP
