#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "../game_state/game_state.hpp"

#include "effect/penalty/penalty.hpp"
#include "effect_price/effect_price.hpp"
#include "player_state/player_state.hpp"
#include "tetromino/tetromino.hpp"

#include <array>
#include <bitset>
#include <memory>

using GameStatePtr = std::shared_ptr<GameState>;

class GameEngine {
  public:
    enum class GameModeFeature {
        PenaltyRows,
        Effects,
        SelectPenaltyTarget,
        NumGameModeFeatures,
    };

    static constexpr size_t numFeatures =
        static_cast<size_t>(GameModeFeature::NumGameModeFeatures);

    using FeaturesBitset = std::bitset<GameEngine::numFeatures>;
    using FeaturesMap = std::array<FeaturesBitset, numFeatures>;

  private:
    // #### Features-related ####

    const static FeaturesMap featuresBitsets;

    /**
     * @brief Checks whether the given feature is enabled for the current
     * GameMode.
     */
    bool checkFeatureEnabled(GameModeFeature gameModeFeatures) const;

    // #### GameState ####

    GameStatePtr pGameState_;

  public:
    /**
     * @brief Constructor
     *
     * @param pGameState A shared pointer to the GameState that the GameEngine
     * should manage.
     */
    GameEngine(const GameStatePtr &pGameState);
    GameEngine(const GameEngine &) = default;
    GameEngine(GameEngine &&) = default;
    GameEngine &operator=(const GameEngine &) = default;
    GameEngine &operator=(GameEngine &&) = default;

    ~GameEngine() = default;

  private:
    /**
     * @brief Sends the given penalty to the sender's selected target.
     */
    void sendPenaltyEffect(PlayerID senderID, Penalty::PenaltyType penaltyType);

    /**
     * @brief Makes the sender send penalty rows to its chosen target.
     */
    void sendPenaltyRows(PlayerID senderID, size_t numRows);

    /**
     * @brief Changes the given player's target to the new target.
     * @param playerID The player whose target will be changed.
     * @param target The new target.
     */
    void selectTarget(PlayerID playerID, PlayerID target);

    /**
     * @brief Returns the number of points awarded for clearing
     * the given number of rows.
     */
    Score calculatePointsClearedRows(size_t numClearedRows);

    /**
     * @brief Returns the amount of Energy awarded to the player for clearing
     * the given number of rows.
     */
    Energy calculateEnergyClearedRows(size_t numClearedRows);

    /**
     * @brief Inserts two mini tetrominoes at the front of the given player's
     * tetrominoes queue.
     */
    void handleMiniTetrominoes(PlayerID playerID);

  public:
    /**
     * @brief Changes the given player's target to the new target.
     * @param playerID The player whose target will be changed.
     * @param target The new target.
     */
    void selectNextAliveTarget(PlayerID playerID);

    /**
     * @brief Returns true if the given player has enough energy to buy the
     * given effect; false otherwise.
     */
    bool checkCanBuyEffect(PlayerID buyerID, EffectType effectType);

    /**
     * @brief Makes the given player buy the given effect if he has enough
     * energy for it, stashes the effect for later or activates it instantly.
     */
    void tryBuyEffect(PlayerID playerID, EffectType effectType,
                      bool stashForLater = false);

    /**
     * @brief Makes the given player select the next item in the effect
     * selector.
     */
    void selectNextEffect(PlayerID playerID);

    /**
     * @brief Makes the given player select the prev item in the effect
     * selector.
     */
    void selectPrevEffect(PlayerID playerID);

    /**
     * @brief Moves the player's active Tetromino in the given direction if
     * possible.
     */
    void tryMoveActive(PlayerID playerID, TetrominoMove tetrominoMove);

    /**
     * @brief Drops the active Tetromino until it hits the bottom or an
     * occupied cell.
     */
    void bigDrop(PlayerID playerID);

    /**
     * @brief Moves the next Tetromino from the queue to hold.
     */
    void holdNextTetromino(PlayerID playerID);

    /**
     * @brief Rotates the player's active Tetromino in the given direction
     * if possible.
     */
    void tryRotateActive(PlayerID playerID, bool rotateClockwise);

    /**
     * @brief Makes a clock tick happen for the given player.
     */
    void clockTick(PlayerID playerID);

    void emptyPenaltyStash(PlayerID playerID);
};

#endif // GAME_ENGINE_HPP
