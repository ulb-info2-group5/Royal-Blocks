#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../game_mode/game_mode.hpp"
#include "../player_state/player_state.hpp"
#include "../player_tetris/player_tetris.hpp"
#include "tetris/tetris.hpp"

#include <nlohmann/json.hpp>

#include <vector>

class GameState {
  private:
    bool isFinished_;
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

    std::optional<UserID> getWinner() const;

    /**
     * @brief Returns a pointer to the PlayerState of the player whose
     * userID matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param userID The player's ID.
     */
    PlayerStatePtr getPlayerState(UserID userID);

    /**
     * @brief Returns a pointer to the Tetris of the player whose userID
     * matches the given one.
     *
     * Returns nullptr no player was found.
     *
     * @param userID The player's ID.
     */
    TetrisPtr getTetris(UserID userID);

    /**
     * @brief Returns the playerToTetris vector member.
     */
    std::vector<PlayerTetris> &getPlayerToTetris();

    void setIsFinished(bool isFinished = true);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serializeForPlayer(UserID userID) const;

    nlohmann::json serializeForViewer() const;
};

#endif // GAME_STATE_HPP
