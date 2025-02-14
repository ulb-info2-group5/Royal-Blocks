#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../game_mode/game_mode.hpp"
#include "../player_state/player_state.hpp"
#include "game_state_view.hpp"
#include "tetris/tetris.hpp"

#include <vector>

// TODO: For getPlayerState and getTetris, might wanna use
// optional<reference_wrapper> to avoid raw pointers.

using PlayerStateTetris = std::pair<PlayerState, Tetris>;

class GameState : public GameStateView {
  private:
    GameMode gameMode_;

    std::vector<PlayerStateTetris> playerToTetris_;

  public:
    /**
     * @brief Constructs a GameState object with given game-mode.
     * @param gameMode The game-mode
     */
    GameState(GameMode gameMode);
    GameState(const GameState &) = default;
    GameState(GameState &&) = delete;
    GameState &operator=(const GameState &) = default;
    GameState &operator=(GameState &&) = delete;

    ~GameState() = default;

    /* ---------------------------------------------------------
     *                  GameStateView Interface
     * ---------------------------------------------------------*/

    const std::vector<PlayerStateTetris> &getPlayerToTetris() const override;

    const PlayerState *getPlayerState(PlayerID playerID) const override;

    const Tetris *getTetris(PlayerID playerID) const override;

    GameMode getGameMode() const override;

    std::optional<PlayerID> getWinner() const override;

    /* ---------------------------------------------------------------
     *          Non-const Methods (not part of GameStateView)
     * ---------------------------------------------------------------*/

    /**
     * @brief Returns a pointer to the PlayerState of the player whose
     * PlayerID matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param playerID The player's ID.
     */
    PlayerState *getPlayerState(PlayerID playerID);

    /**
     * @brief Returns a pointer to the Tetris of the player whose PlayerID
     * matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param playerID The player's ID.
     */
    Tetris *getTetris(PlayerID playerID);

    class CircularIt {
      private:
        size_t currentIdx_;
        std::vector<PlayerStateTetris> &playerToTetris_;

      public:
        CircularIt(std::vector<PlayerStateTetris> &playerToTetris,
                   size_t startIdx)
            : currentIdx_{startIdx}, playerToTetris_(playerToTetris) {}

        PlayerStateTetris &operator*() const {
            return playerToTetris_.at(currentIdx_);
        }

        CircularIt &operator++() {
            currentIdx_ = (currentIdx_ + 1) % playerToTetris_.size();
            return *this;
        }

        CircularIt &operator--() {
            currentIdx_ = (currentIdx_ + playerToTetris_.size() - 1)
                          % playerToTetris_.size();
            return *this;
        }

        bool operator==(const CircularIt &other) const {
            // TODO: Add this check to the operator must define operator== for
            // PlayerState first for this:
            // playerToTetris_ == other.playerToTetris_
            return currentIdx_ == other.currentIdx_;
        }

        bool operator!=(const CircularIt &other) const {
            return !operator==(other);
        }
    };

    CircularIt getCircularItAt(size_t idx);

    CircularIt getCircularItEnd();

    /**
     * @brief Returns an iterator on the PlayerStateTetris that matches
     * the given PlayerID.
     */
    CircularIt getCircularIt(PlayerID playerID);
};

#endif // GAME_STATE_HPP
