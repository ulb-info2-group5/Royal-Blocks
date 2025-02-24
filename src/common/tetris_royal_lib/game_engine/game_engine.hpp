#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "../game_state/game_state.hpp"

#include "effect/penalty/penalty_type.hpp"
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
        NumGameModeFeature,
    };

    static constexpr size_t numFeatures =
        static_cast<size_t>(GameModeFeature::NumGameModeFeature);

    static constexpr size_t numGameMode =
        static_cast<size_t>(GameMode::NumGameMode);

    using FeaturesBitset = std::bitset<GameEngine::numFeatures>;
    using FeaturesMap = std::array<FeaturesBitset, numGameMode>;

  private:
    // #### Features-related ####

    static constexpr auto genFeaturesBitset =
        [](std::initializer_list<GameEngine::GameModeFeature> enabledFeatures)
        -> GameEngine::FeaturesBitset {
        GameEngine::FeaturesBitset bitset;

        for (GameEngine::GameModeFeature features : enabledFeatures) {
            bitset.set(static_cast<size_t>(features));
        }

        return bitset;
    };

    constexpr static FeaturesMap featuresBitsets =
        []() -> GameEngine::FeaturesMap {
        GameEngine::FeaturesMap featuresPerGameMode;

        featuresPerGameMode.at(static_cast<size_t>(GameMode::Endless)) =
            genFeaturesBitset({
                // Endless features go here
            });

        featuresPerGameMode.at(static_cast<size_t>(GameMode::Dual)) =
            genFeaturesBitset({
                // Dual features go here
                GameModeFeature::PenaltyRows,
            });

        featuresPerGameMode.at(static_cast<size_t>(GameMode::Classic)) =
            genFeaturesBitset({
                // Classic features go here
                GameModeFeature::PenaltyRows,
                GameModeFeature::SelectPenaltyTarget,
            });

        featuresPerGameMode.at(static_cast<size_t>(
            GameMode::RoyalCompetition)) = genFeaturesBitset({
            // Royal features go here
            GameModeFeature::Effects,
            GameModeFeature::SelectPenaltyTarget,
        });

        return featuresPerGameMode;
    }();

  public:
    /**
     * @brief Checks whether the given feature is enabled for the given
     * GameMode.
     */
    static bool checkFeatureEnabled(GameMode gameMode,
                                    GameModeFeature gameModeFeature);

  private:
    /**
     * @brief Checks whether the given feature is enabled for the current
     * GameMode.
     */
    bool checkFeatureEnabled(GameModeFeature gameModeFeature) const;

    // #### GameState ####

    GameStatePtr pGameState_;

    // #### Effects Helpers ####

    /**
     * @brief Returns true if the given player currently has the inverted
     * controls penalty.
     */
    bool shouldReverseControls(PlayerID playerID);

    /**
     * @brief Returns true if the given player currently has the input lock
     * penalty.
     */
    bool shouldLockInput(PlayerID playerID);

    /**
     * @brief Returns the opposite move of the given TetrominioMove
     */
    TetrominoMove invertTetrominoMove(TetrominoMove tetrominoMove);

    /**
     * @brief Returns true if the tick should be ignored for the given player.
     * (Due to slowdown bonus).
     */
    bool shouldIgnoreTick(PlayerID playerID);

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
    void sendPenaltyEffect(PlayerID senderID, PenaltyType penaltyType);

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

    /**
     * @brief Destroys a 2x2 block in a random position in the player's grid if
     * there one was found;otherwise, doesn't do anything.
     */
    void handleLightning(PlayerID playerID);

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

    /**
     * @brief Sends all the penalties that were stashed.
     */
    void emptyPenaltyStash(PlayerID playerID);
};

#endif // GAME_ENGINE_HPP
