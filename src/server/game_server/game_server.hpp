#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "../../common/bindings/in_game/select_target.hpp"

#include "../network/client_link/client_link.hpp"
#include "game_engine/game_engine.hpp"
#include "player_state/player_state.hpp"

#include <boost/asio.hpp>

using GameID = size_t;

using CallBackFinishGame = std::function<void(GameID)>;

class ClientLink;

struct Player {
    UserID userID;
    std::string username;
};

class GameServer {
  private:
    static constexpr size_t INITIAL_TICK_DELAY_MS = 1000;
    static constexpr size_t MIN_TICK_DELAY_MS = 1000;
    static constexpr size_t DECREASE_TICK_DELAY_MS = 20;
    size_t tickDelayMs_;

    boost::asio::io_context context_;
    boost::asio::steady_timer tickTimer_;
    GameStatePtr pGameState_;
    GameEngine engine;
    GameID gameId_;

    CallBackFinishGame callBackFinishGame_;
    std::vector<std::weak_ptr<ClientLink>> pClientLinks_;
    /**
     * @brief Signals the engine that an engine tick occured. Resets the timer
     * for the next tick.
     */
    void onTimerTick();

  public:
    /**
     * @brief Constructor.
     */
    GameServer(GameMode gameMode, std::vector<Player> &&players, GameID id,
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

    void addClientLink(std::weak_ptr<ClientLink> clientLink);

    // === getters ===

    boost::asio::io_context &getIoContext();

    std::vector<UserID> getVectorPlayersId();

    const std::vector<std::weak_ptr<ClientLink>> &getClientLinks();

    GameMode getGameMode() const;

    int getPlayerScore(const UserID userId) const;
};

#endif // GAME_SERVER_HPP
