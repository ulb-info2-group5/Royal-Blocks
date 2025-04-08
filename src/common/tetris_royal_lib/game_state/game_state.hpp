#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../game_mode/game_mode.hpp"
#include "../player_state/player_state.hpp"
#include "../player_tetris/player_tetris.hpp"
#include "tetris/tetris.hpp"

#include <nlohmann/json.hpp>

#include <map>
#include <vector>

class GameState {
  private:
    bool isFinished_;
    const GameMode gameMode_;
    std::map<UserID, PlayerTetris> userToPlayerTetris_;

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

    /**
     * @brief Returns the GameMode.
     */
    GameMode getGameMode() const;

    /**
     * @brief Returns the winner if there's one, nullopt otherwise.
     */
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
     * @brief Returns the user to playerTetris map.
     */
    std::map<UserID, PlayerTetris> &getUserToPlayerTetris();

    /**
     * @brief Sets the `isFinished_` flag to the specified value.
     *
     * This flag indicates whether the game state is finished. It is not updated
     * automatically by the GameState itself, so it must be explicitly set by
     * the component responsible for managing the GameState instance.
     *
     * @param isFinished Whether the game state should be marked as finished.
     */
    void setIsFinished(bool isFinished = true);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the GameState to json, hiding any information
     * the specified player should not have access to.
     *
     * @param userID The ID of the player for whom the serialization is
     * intended.
     */
    nlohmann::json serializeForPlayer(UserID userID) const;

    /**
     * @brief Serializes the GameState to JSON for a viewer (spectator),
     * excluding all secret information specific to the player themself.
     */
    nlohmann::json serializeForViewer() const;
};

using GameStatePtr = std::shared_ptr<GameState>;

#endif // GAME_STATE_HPP
