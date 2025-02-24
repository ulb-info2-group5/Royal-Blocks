#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../game_mode/game_mode.hpp"
#include "../player_state/player_state.hpp"
#include "../player_tetris/player_tetris.hpp"
#include "tetris/tetris.hpp"

#include <nlohmann/json.hpp>

#include <vector>

// TODO: For getPlayerState and getTetris, might wanna use
// optional<reference_wrapper> to avoid raw pointers.

class GameState {
  private:
    const GameMode gameMode_;

    std::vector<PlayerTetris> playerToTetris_;

  public:
    /**
     * @brief Constructs a GameState object with given game-mode.
     * @param gameMode The game-mode
     */
    GameState(GameMode gameMode, std::vector<PlayerState> &&playerStates);
    GameState(const GameState &) = default;
    GameState(GameState &&) = default;
    GameState &operator=(const GameState &) = delete;
    GameState &operator=(GameState &&) = delete;

    ~GameState() = default;

    GameMode getGameMode() const;

    std::optional<PlayerID> getWinner() const;

    /**
     * @brief Returns a pointer to the PlayerState of the player whose
     * PlayerID matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param playerID The player's ID.
     */
    PlayerStatePtr getPlayerState(PlayerID playerID);

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
        std::vector<PlayerTetris> &playerToTetris_;

      public:
        CircularIt(std::vector<PlayerTetris> &playerToTetris, size_t startIdx)
            : currentIdx_{startIdx}, playerToTetris_(playerToTetris) {}

        PlayerTetris &operator*() const {
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
            // TODO: Add this check to the operator must define operator==
            // for PlayerState first for this: playerToTetris_ ==
            // other.playerToTetris_
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

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serializeFor(PlayerID playerID) const;
};

#endif // GAME_STATE_HPP
