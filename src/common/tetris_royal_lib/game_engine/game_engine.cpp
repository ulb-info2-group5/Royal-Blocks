#include "game_engine.hpp"
#include "../effect_price/effect_price.cpp"
#include "../game_mode/game_mode.hpp"
#include "effect_price/effect_price.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <cassert>
#include <optional>
#include <variant>

static constexpr auto genFeaturesBitset =
    [](std::initializer_list<GameEngine::GameModeFeature> enabledFeatures)
    -> GameEngine::FeaturesBitset {
    GameEngine::FeaturesBitset bitset;

    for (GameEngine::GameModeFeature features : enabledFeatures) {
        bitset.set(static_cast<size_t>(features));
    }

    return bitset;
};

const GameEngine::FeaturesMap GameEngine::featuresBitsets =
    []() -> GameEngine::FeaturesMap {
    GameEngine::FeaturesMap featuresPerGameMode;

    featuresPerGameMode.at(static_cast<size_t>(GameMode::Endless)) =
        genFeaturesBitset({
            // Endless features go here
        });

    featuresPerGameMode.at(static_cast<size_t>(GameMode::Dual)) =
        genFeaturesBitset({
            // Dual features go here
        });

    featuresPerGameMode.at(static_cast<size_t>(GameMode::Classic)) =
        genFeaturesBitset({
            // Classic features go here
            GameModeFeature::SelectPenaltyTarget,
        });

    featuresPerGameMode.at(static_cast<size_t>(GameMode::RoyalCompetition)) =
        genFeaturesBitset({
            // Royal features go here
            GameModeFeature::Effects,
            GameModeFeature::SelectPenaltyTarget,
        });

    return featuresPerGameMode;
}();

bool GameEngine::checkFeaturesEnabled(GameModeFeature gameModeFeature) const {
    return featuresBitsets.at(static_cast<size_t>(pGameState_->getGameMode()))
        .test(static_cast<size_t>(gameModeFeature));
}

GameEngine::GameEngine(const GameStatePtr &pGameState)
    : pGameState_(pGameState) {}

void GameEngine::sendPenaltyEffect(PlayerID sender,
                                   Penalty::PenaltyType penaltyType) {
    if (!checkFeaturesEnabled(GameModeFeature::Effects)
        || !checkFeaturesEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    // TODO: Decide whether a player can have no selected target at the
    // beginning of the game. If so, one more case to handle with the optional
    // (nullopt)

    std::optional<PlayerID> target =
        pGameState_->getPlayerState(sender)->getPenaltyTarget();

    pGameState_->getPlayerState(target.value())->receivePenalty(penaltyType);
}

bool GameEngine::checkCanBuyEffect(PlayerID buyerID, EffectType effectType) {
    if (!checkFeaturesEnabled(GameModeFeature::Effects)) {
        return false;
    }

    return pGameState_->getPlayerState(buyerID)->getEnergy()
           >= getEffectPrice(effectType);
}

void GameEngine::tryBuyEffect(PlayerID buyerID, EffectType effectType) {
    if (!checkFeaturesEnabled(GameModeFeature::Effects)) {
        return;
    }

    // Not enough energy to buy the effect
    if (!checkCanBuyEffect(buyerID, effectType)) {
        return;
    }

    // Take the player's energy (effect price)
    pGameState_->getPlayerState(buyerID)->decreaseEnergy(
        getEffectPrice(effectType));

    std::visit(
        [&](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, Bonus::BonusType>) {
                // Bonus case
                pGameState_->getPlayerState(buyerID)->grantBonus(effectType);
            } else if constexpr (std::is_same_v<T, Penalty::PenaltyType>) {
                // Penalty case
                sendPenaltyEffect(buyerID, effectType);
            }
        },
        effectType);
}

void GameEngine::selectTarget(PlayerID playerID, PlayerID target) {
    if (!checkFeaturesEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->setPenaltyTarget(target);
}

// TODO
void GameEngine::selectNextAliveTarget(PlayerID playerID) {
    if (!checkFeaturesEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    // Assume that if no target had been chosen by this player previously,
    // the target was the player himslef so that it chooses the player after
    // himself (in the getPlayerToTetris() vector) as next target.
    PlayerID prevTargetID =
        pGameState_->getPlayerState(playerID)->getPenaltyTarget().value_or(
            playerID);

    GameState::CircularIt playerSelfIt = pGameState_->getCircularIt(playerID);

    GameState::CircularIt prevTargetIt =
        pGameState_->getCircularIt(prevTargetID);

    GameState::CircularIt newTargetIt = prevTargetIt;

    do {
        ++newTargetIt;
        // TODO: Check that this is correct
        // avoid stopping the player himself
        if (newTargetIt == playerSelfIt) {
            ++newTargetIt;
        }
    } while (newTargetIt != prevTargetIt && !(*newTargetIt).first.isAlive());

    // NOTE: This should never happen, if it does, the game should have ended
    // earlier because there is only one player left.
    assert(newTargetIt != playerSelfIt);

    PlayerID newTargetID = (*newTargetIt).first.getPlayerID();

    pGameState_->getPlayerState(playerID)->setPenaltyTarget(newTargetID);
}

void GameEngine::selectNextEffect(PlayerID playerID) {

    if (!checkFeaturesEnabled(GameModeFeature::Effects)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->selectNextEffect();
}

void GameEngine::selectPrevEffect(PlayerID playerID) {

    if (!checkFeaturesEnabled(GameModeFeature::Effects)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->selectPrevEffect();
}

void GameEngine::tryMoveActive(PlayerID playerID, TetrominoMove tetrominoMove) {
    pGameState_->getTetris(playerID)->eventTryMoveActive(tetrominoMove);
}

void GameEngine::tryRotateActive(PlayerID playerID, bool rotateClockwise) {
    pGameState_->getTetris(playerID)->eventTryRotateActive(rotateClockwise);
}
