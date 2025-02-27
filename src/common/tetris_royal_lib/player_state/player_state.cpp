#include "player_state.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "effect/penalty/penalty_type.hpp"
#include "effect/penalty/speed_up.hpp"
#include "effect_selector/effect_selector.hpp"

#include <optional>

PlayerState::PlayerState(PlayerID playerID, Score score)
    : TetrisObserver{}, playerID_{playerID}, score_{score}, isAlive_{true},
      penaltyTarget_{std::nullopt}, energy_{std::nullopt},
      receivedPenaltiesQueue_{std::nullopt}, grantedBonusesQueue_{std::nullopt},
      effectSelector_{std::nullopt}, pActiveBonus_{nullptr},
      pActivePenalty_{nullptr}, engineTicksSinceLastTick_{0} {}

void PlayerState::toggleEffects(bool activated) {
    if (activated) {
        energy_ = Energy{};
    } else {
        energy_ = std::nullopt;
    }

    if (activated) {
        receivedPenaltiesQueue_ = std::queue<PenaltyType>{};
        grantedBonusesQueue_ = std::queue<BonusType>{};
    } else {
        receivedPenaltiesQueue_ = std::nullopt;
        grantedBonusesQueue_ = std::nullopt;
    }

    if (activated) {
        effectSelector_ = EffectSelector{};
    } else {
        effectSelector_ = std::nullopt;
    }

    if (activated) {
        stashedPenalties_ = std::deque<PenaltyType>{};
    } else {
        stashedPenalties_ = std::nullopt;
    }
}

/* ------------------------------------------------
 *              Common to all GameModes
 * ------------------------------------------------*/

PlayerID PlayerState::getPlayerID() const { return playerID_; }

Score PlayerState::getScore() const { return score_; }

void PlayerState::increaseScore(Score val) { score_ += val; }

bool PlayerState::isAlive() const { return isAlive_; }

void PlayerState::setAlive(bool isAlive) { isAlive_ = isAlive; }

/* ------------------------------------------------
 *      Classic & RoyalCompetition Specific
 * ------------------------------------------------*/

std::optional<PlayerID> PlayerState::getPenaltyTarget() const {
    return penaltyTarget_;
}

void PlayerState::setPenaltyTarget(PlayerID playerID) {
    // WARN: This member could be nullopt for multiple reasons:
    // 1. The GameMode is neither Classic nor RoyalCompetition.
    // 2. Viewers shouldn't see other players's target.
    // 3. Players shouldn't see other player's target.
    // 4. There is no player selected at the beginning. (Depending on what we
    // choose later)
    penaltyTarget_ = playerID;
}

/* ------------------------------------------------
 *      RoyalCompetition Specific
 * ------------------------------------------------*/

std::optional<Energy> PlayerState::getEnergy() const { return energy_; }

void PlayerState::increaseEnergy(Energy amount) {
    if (!energy_.has_value()) {
        return;
    }

    energy_.value() += amount;
}

void PlayerState::decreaseEnergy(Energy amount) {
    if (!energy_.has_value()) {
        return;
    }

    energy_.value() -= amount;
}

std::optional<EffectType> PlayerState::getSelectedEffect() {
    return effectSelector_.and_then(
        [](auto &selector) -> std::optional<EffectType> {
            return selector.getSelectedEffect();
        });
}

void PlayerState::grantBonus(BonusType bonus) {
    if (!grantedBonusesQueue_.has_value()) {
        return;
    }

    grantedBonusesQueue_->push(bonus);
}

void PlayerState::receivePenalty(PenaltyType penalty) {
    if (!receivedPenaltiesQueue_.has_value()) {
        return;
    }

    receivedPenaltiesQueue_->push(penalty);
}

std::optional<BonusType> PlayerState::fetchGrantedBonus() {
    return grantedBonusesQueue_.and_then([](auto &queue) {
        std::optional<BonusType> ret;

        if (queue.empty()) {
            ret = std::nullopt;
        } else {
            ret = queue.front();
            queue.pop();
        }

        return ret;
    });
}

std::optional<PenaltyType> PlayerState::fetchReceivedPenalty() {
    return receivedPenaltiesQueue_.and_then([](auto &queue) {
        std::optional<PenaltyType> ret;

        if (queue.empty()) {
            ret = std::nullopt;
        } else {
            ret = queue.front();
            queue.pop();
        }

        return ret;
    });
}

void PlayerState::setActivePenalty(TimedPenaltyPtr pTimedPenalty) {
    pActivePenalty_ = pTimedPenalty;
}

void PlayerState::selectEffect(EffectType effectType) {
    effectSelector_.and_then([effectType](EffectSelector &effectSelector) {
        effectSelector.select(effectType);
        return std::make_optional<EffectSelector>();
    });
}

void PlayerState::setActiveBonus(TimedBonusPtr pTimedBonus) {
    pActiveBonus_ = pTimedBonus;
}

TimedBonusPtr &PlayerState::getActiveBonus() { return pActiveBonus_; }

TimedPenaltyPtr &PlayerState::getActivePenalty() { return pActivePenalty_; }

void PlayerState::selectNextEffect() { effectSelector_->next(); }

void PlayerState::selectPrevEffect() { effectSelector_->prev(); }

void PlayerState::stashPenalty(PenaltyType penalty) {
    stashedPenalties_->push_back(penalty);
}

std::deque<PenaltyType> PlayerState::getStashedPenalties() {
    return std::move(stashedPenalties_.value());
}

bool PlayerState::isGameTick() {
    if (!engineTicksSinceLastTick_.has_value()) {
        // Every tick is a game tick if there is no engineTicksSinceLastTick_
        // member
        return true;
    }

    if (getActivePenalty() != nullptr
        && pActivePenalty_->getPenaltyType() == PenaltyType::SpeedUp) {
        return true;
    }

    return *engineTicksSinceLastTick_ % SpeedUp::SpeedUpFactor == 0;
}

void PlayerState::notifyEngineTick() {
    if (!engineTicksSinceLastTick_.has_value()) {
        return;
    }

    engineTicksSinceLastTick_ =
        (*engineTicksSinceLastTick_ + 1) % SpeedUp::SpeedUpFactor;
}

/* ------------------------------------------------
 *          TetrisObserver
 * ------------------------------------------------*/

void PlayerState::notifyLost() { isAlive_ = false; }

void PlayerState::notifyActiveTetrominoPlaced() {
    if (pActiveBonus_ != nullptr) {
        pActiveBonus_->tetrominoPlaced();
    }

    if (pActivePenalty_ != nullptr) {
        pActivePenalty_->tetrominoPlaced();
    }
}

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json PlayerState::serializeExternal() const {
    nlohmann::json j;
    j["playerID"] = playerID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;

    return j;
}

nlohmann::json PlayerState::serializeSelf() const {
    nlohmann::json j;
    j["playerID"] = playerID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;

    if (penaltyTarget_) {
        j["penaltyTarget"] = *penaltyTarget_;
    } else {
        j["penaltyTarget"] = nullptr;
    }

    if (energy_) {
        j["energy"] = *energy_;
    } else {
        j["energy"] = nullptr;
    }

    if (effectSelector_) {
        j["effectSelector"] = effectSelector_->serialize();
    } else {
        j["effectSelector"] = nullptr;
    }

    if (stashedPenalties_) {
        nlohmann::json j_stashedPenalties = nlohmann::json::array();
        for (const auto &stashedPenalty : *stashedPenalties_) {
            j_stashedPenalties.push_back(stashedPenalty);
        }
        j["stashedPenalties"] = j_stashedPenalties;
    } else {
        j["stashedPenalties"] = nullptr;
    }

    return j;
}
