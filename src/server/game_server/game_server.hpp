/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "../../common/bindings/in_game/select_target.hpp"

#include "../client_link/client_link.hpp"
#include "game_engine/game_engine.hpp"
#include "player_state/player_state.hpp"

#include <asio.hpp>

using GameID = size_t;

using CallBackFinishGame = std::function<void(GameID)>;

class ClientLink;

struct Player {
    UserID userID;
    std::string username;
};

/**
 * @class GameServer
 * @brief handle the progress of a game, manage game packages and send gameState
 *
 */

class GameServer {
  private:
    static constexpr size_t INITIAL_TICK_DELAY_MS = 1000;
    static constexpr size_t MIN_TICK_DELAY_MS = 1000;
    static constexpr size_t DECREASE_TICK_DELAY_MS = 20;
    std::mutex gameMutex_;
    size_t tickDelayMs_;

    asio::io_context context_;
    asio::steady_timer tickTimer_;
    GameStatePtr pGameState_;
    GameEngine engine;
    GameID gameId_;

    CallBackFinishGame callBackFinishGame_;
    // contains the weap_ptr of clients who playing or watching the
    std::vector<std::weak_ptr<ClientLink>> pClientLinks_;
    /**
     * @brief Signals the engine that an engine tick occured. Resets the timer
     * for the next tick.
     */
    void onTimerTick();
    /**
     * @brief delete a user from players
     */
    void erasmePlayer(UserID userID);

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

    /**
     * @brief add clientLink in the clients lists
     */
    void addClientLink(std::weak_ptr<ClientLink> clientLink);

    void quitGameAsViewer(UserID userID);

    // === getters ===

    std::vector<UserID> getVectorPlayersId();

    const std::vector<std::weak_ptr<ClientLink>> &getClientLinks();

    GameMode getGameMode() const;

    int getPlayerScore(const UserID userId) const;
};

#endif // GAME_SERVER_HPP
