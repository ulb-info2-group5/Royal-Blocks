#include "game_state.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "game_engine/game_engine.hpp"
#include "nlohmann/json_fwd.hpp"
#include "player_state/player_state.hpp"
#include "player_tetris/player_tetris.hpp"

#include <memory>
#include <optional>
#include <vector>

GameState::GameState(GameMode gameMode, std::vector<PlayerState> &&playerStates)
    : isFinished_{false}, gameMode_{gameMode} {

    for (size_t i = 0; i < playerStates.size(); i++) {
        PlayerState &playerState = playerStates.at(i);
        size_t numPlayers = playerStates.size();

        playerState.setPenaltyTarget(
            playerStates.at((i + 1) % numPlayers).getUserID());
        playerState.toggleEffects(GameEngine::checkFeatureEnabled(
            gameMode, GameEngine::GameModeFeature::Effects));
        playerToTetris_.emplace_back(
            PlayerTetris{std::make_shared<PlayerState>(playerState)});
    }
}

GameMode GameState::getGameMode() const { return gameMode_; }

std::optional<UserID> GameState::getWinner() const {
    std::optional<UserID> winner;

    for (const PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->isAlive()) {
            if (winner.has_value()) {
                // had already found a player that is
                // still alive -> more than one player
                // alive -> no winner yet.
                return std::nullopt;
            }

            winner = playerStateTetris.pPlayerState->getUserID();
        }
    }

    return winner;
}

PlayerStatePtr GameState::getPlayerState(UserID userID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->getUserID() == userID) {
            return playerStateTetris.pPlayerState;
        }
    }

    return nullptr;
}

TetrisPtr GameState::getTetris(UserID userID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->getUserID() == userID) {
            return playerStateTetris.pTetris;
        }
    }

    return nullptr;
}

std::vector<PlayerTetris> &GameState::getPlayerToTetris() {
    return playerToTetris_;
}

void GameState::setIsFinished(bool isFinished) { isFinished_ = isFinished; }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json GameState::serializeForPlayer(UserID userID) const {
    nlohmann::json j;

    j["isFinished"] = isFinished_;
    j["gameMode"] = gameMode_;

    j["externals"] = nlohmann::json::array();

    for (const auto &playerTetris : playerToTetris_) {
        if (playerTetris.pPlayerState->getUserID() == userID) {
            j["self"] = playerTetris.serializeSelf();
        } else {
            j["externals"].push_back(playerTetris.serializeExternal());
        }
    }

    // add the effects that the players can buy with their price
    j["bonusToPrice"] = nlohmann::json::array();
    j["penaltyToPrice"] = nlohmann::json::array();
    if (GameEngine::checkFeatureEnabled(gameMode_,
                                        GameEngine::GameModeFeature::Effects)) {
        // bonuses
        for (size_t i = 0; i < static_cast<size_t>(BonusType::NumBonusType);
             i++) {
            BonusType bonusType = static_cast<BonusType>(i);
            j["bonusToPrice"].push_back({bonusType, getEffectPrice(bonusType)});
        }
        // penalties
        for (size_t i = 0; i < static_cast<size_t>(PenaltyType::NumPenaltyType);
             i++) {
            PenaltyType penaltyType = static_cast<PenaltyType>(i);
            j["penaltyToPrice"].push_back(
                {penaltyType, getEffectPrice(penaltyType)});
        }
    }

    return j;
}

nlohmann::json GameState::serializeForViewer() const {
    nlohmann::json j;

    j["isFinished"] = isFinished_;
    j["gameMode"] = gameMode_;

    j["externals"] = nlohmann::json::array();

    for (const auto &playerTetris : playerToTetris_) {
        j["externals"].push_back(playerTetris.serializeExternal());
    }

    return j;
}
