#ifndef GAME_STATE_VIEW_HPP
#define GAME_STATE_VIEW_HPP

#include "../game_mode/game_mode.hpp"
#include "../player_state/player_state.hpp"
#include "tetris/tetris.hpp"

#include <optional>

/**
 * @brief A view of a GameState (expose only the methods required to view
 * the GameState, without modifying it).
 */
class GameStateView {
  public:
    GameStateView() = default;
    GameStateView(const GameStateView &) = default;
    GameStateView(GameStateView &&) = delete;
    GameStateView &operator=(const GameStateView &) = default;
    GameStateView &operator=(GameStateView &&) = delete;

    virtual ~GameStateView() = default;

    /**
     * @brief Returns a const reference to the vector of pairs
     * PlayerState-Tetris.
     */
    virtual const std::vector<std::pair<PlayerState, Tetris>> &
    getPlayerToTetris() const = 0;

    /**
     * @brief Returns a pointer to the const PlayerState of the player whose
     * PlayerID matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param playerID The player's ID.
     */
    virtual const PlayerState *getPlayerState(PlayerID playerID) const = 0;

    /**
     * @brief Returns a pointer to the const Tetris of the player whose PlayerID
     * matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param playerID The player's ID.
     */
    virtual const Tetris *getTetris(PlayerID playerID) const = 0;

    /**
     * @brief Returns the game-mode.
     */
    virtual GameMode getGameMode() const = 0;

    /**
     * @brief Returns the winner.
     */
    virtual std::optional<PlayerID> getWinner() const = 0;
};

#endif // GAME_STATE_VIEW_HPP
