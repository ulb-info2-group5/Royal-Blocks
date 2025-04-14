#ifndef ABSTRACT_GAME_DISPLAY_HPP
#define ABSTRACT_GAME_DISPLAY_HPP

#include "../common/types/types.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"
#include "effect/effect_type.hpp"

#include <optional>

class Controller;

/**
 * @brief Abstract base class for GameDisplay implementations (TUI & GUI).
 *
 * @note Maintains an internal game state using a double-buffering system. The
 * state is updated via updateGameState(), which queries the controller
 * and copies the new game state. This design avoids using mutexes within
 * the frontend logic.
 *
 * @note To refer to opponents, use their index in client::GameState, not their
 * userId.
 */
class AbstractGameDisplay {
  private:
    std::variant<client::GameState, client::GameStateViewer> gameState_;

    Controller &controller_;

  public:
    /**
         * @brief Extra metadata (besides color) for a Tetris cell belonging to
       the local player.
         */
    enum class SelfCellType {
        Active,  // Part of the active tetromino
        Preview, // Part of the preview tetromino
        Placed,  // Occupied & placed in the board
    };

    enum class Color {
        Black,
        White,
        Grey,
        DarkBlue,
        LightBlue,
        Purple,
        Red,
        Orange,
        Pink,
        Green,
        Yellow
    };

  protected:
    /**
     * @brief Constructor.
     */
    AbstractGameDisplay(Controller &controller);
    AbstractGameDisplay(const AbstractGameDisplay &) = default;
    AbstractGameDisplay(AbstractGameDisplay &&) = default;
    AbstractGameDisplay &operator=(const AbstractGameDisplay &) = delete;
    AbstractGameDisplay &operator=(AbstractGameDisplay &&) = delete;

    /**
     * @brief Returns the color corresponding to the given colorID.
     */
    static Color colorIdToColor(unsigned colorID);

    /**
     * @brief Returns the given opponent's userId.
     */
    UserID getNthOpponentUserID(size_t n) const;

    /**
     * @brief Returns the board's height.
     */
    size_t getBoardHeight() const;

    /**
     * @brief Selects the player at the targetIndex position in the gamestate as
     * the target.
     */
    void selectTarget(size_t targetIndex);

    /**
     * @brief Notifies the controller of a key-press.
     */
    void handleKeyPress(const std::string &key);

    /**
     * @brief Quits the game.
     */
    void quitGame();

    /**
     * @brief Returns the selected effect type.
     */
    EffectType getSelectedEffectType() const;

    /**
     * @brief Set the given effect type as selected.
     */
    void setSelectedEffectType(EffectType effectType);

    /**
     * @brief Buys the given effect.
     */
    void buyEffect(EffectType effectType);

    /**
     * @brief Updates the game state.
     */
    void updateGameState();

    /**
     * @brief Returns the board' width.
     */
    size_t getBoardWidth() const;

    /**
     * @brief Returns the player's score.
     */
    Energy getSelfScore() const;

    /**
     * @brief Returns the player's current target.
     */
    std::optional<UserID> getSelectedTarget() const;

    /**
     * @brief Returns the player's energy.
     */
    Score getSelfEnergy() const;

    /**
     * @brief Returns the current game-mode.
     */
    GameMode getGameMode() const;

    /**
     * @brief Returns a pair<colorId, SelfCellType>
     * @see SelfCellType for documentation.
     */
    std::optional<std::pair<unsigned, SelfCellType>>
    selfCellInfoAt(int x, int y) const;

    /**
     * @brief Returns the player's username.
     */
    const std::string &getSelfUsername() const;

    /**
     * @brief Returns the color ID of the cell at (x, y) on the given
     * opponent's board.
     */
    std::optional<unsigned> opponentsBoardGetColorIdAt(size_t opponentIdx,
                                                       int x, int y) const;

    /**
     * @brief Returns the given opponent's username.
     */
    const std::string &getOpponentUsername(size_t opponentIdx) const;

    /**
     * @brief Checks whether the given opponent is still alive.
     */
    bool checkOpponentAlive(size_t opponentIdx) const;

    /**
     * @brief Returns the number of opponent.
     */
    size_t getNumOpponents() const;

    /**
     * @brief Returns the nth tetromino in the tetrominoes-queue.
     */
    const client::Tetromino &getTetrominoQueueNth(size_t tetrominoIdx) const;

    /**
     * @brief Returns a pointer to the hold Tetromino (nullptr if none).
     *
     * NOTE: Would have been better to return optional<client::Tetromino&> but
     * impossible according to
     * https://en.cppreference.com/w/cpp/utility/optional.
     */
    const client::Tetromino *getHoldTetromino() const;

    /**
     * @brief Returns the tetrominoes-queue size.
     */
    size_t getTetrominoQueuesSize() const;

    /**
     * @brief Returns a associating each available EffectType to its price in
     * energy.
     */
    const std::vector<std::pair<EffectType, Energy>> &getEffectPrices() const;

    /**
     * @brief Returns the active penalty's name and elapsedTime (between 0 &
     * 1).
     */
    std::optional<std::pair<std::string, double>> getPenaltyInfo() const;

    /**
     * @brief Returns the active bonus's name and elapsedTime (between 0 &
     * 1).
     */
    std::optional<std::pair<std::string, double>> getBonusInfo() const;

    /**
     * @brief Returns true if the player is spectating.
     */
    bool isSpectating() const;

    /**
     * @brief Returns true if the player is the winner.
     * @note Always false in endless mode.
     */
    bool isWinner() const;

    /**
     * @brief Returns true if the gamestate indicates that the game is finished.
     */
    bool gameIsFinished() const;
};

#endif // ABSTRACT_GAME_DISPLAY_HPP
