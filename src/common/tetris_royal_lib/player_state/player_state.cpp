#include "player_state.hpp"
#include "effect/penalty/penalty.hpp"
#include "effect_selector/effect_selector.hpp"

#include <optional>

PlayerState::PlayerState(PlayerID playerID, Score score)
    : playerID_{playerID}, score_{score}, isAlive_{true},
      penaltyTarget_{std::nullopt}, energy_{std::nullopt},
      receivedPenaltiesQueue_{std::nullopt}, grantedBonusesQueue_{std::nullopt},
      effectSelector_{std::nullopt}, pActiveBonus_{nullptr},
      pActivePenalty_{nullptr} {}

void PlayerState::toggleEffects(bool activated) {
    if (activated) {
        energy_ = Energy{};
    } else {
        energy_ = std::nullopt;
    }

    if (activated) {
        receivedPenaltiesQueue_ = std::queue<Penalty::PenaltyType>{};
        grantedBonusesQueue_ = std::queue<Bonus::BonusType>{};
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
        stashedPenalties_ = std::queue<Penalty::PenaltyType>{};
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

void PlayerState::grantBonus(Bonus::BonusType bonus) {
    if (!grantedBonusesQueue_.has_value()) {
        return;
    }

    grantedBonusesQueue_->push(bonus);
}

void PlayerState::receivePenalty(Penalty::PenaltyType penalty) {
    if (!receivedPenaltiesQueue_.has_value()) {
        return;
    }

    receivedPenaltiesQueue_->push(penalty);
}

std::optional<Bonus::BonusType> PlayerState::fetchGrantedBonus() {
    return grantedBonusesQueue_.and_then([](auto &queue) {
        std::optional<Bonus::BonusType> ret;
        queue.pop();
        return ret;
    });
}

std::optional<Penalty::PenaltyType> PlayerState::fetchReceivedPenalty() {
    return receivedPenaltiesQueue_.and_then([](auto &queue) {
        std::optional<Penalty::PenaltyType> ret;
        queue.pop();
        return ret;
    });
}

void PlayerState::setActivePenalty(AbstractTimedEffectPtr pTimedEffect) {
    // TODO: if *pTimedEffect doesn't derive from Penalty,
    // throw std::invalid_argument("Attempted to set an effect that
    // doesn't " "derive from penalty as active-penalty.");

    pActivePenalty_ = pTimedEffect;
}

void PlayerState::setActiveBonus(AbstractTimedEffectPtr pTimedEffect) {
    // TODO: if *pTimedEffect doesn't derive from Bonus,
    // throw std::invalid_argument("Attempted to set an effect that doesn't
    // derive from bonus as active-bonus.");

    pActiveBonus_ = pTimedEffect;
}

AbstractTimedEffectPtr PlayerState::getActiveBonus() const {
    return pActiveBonus_;
}

AbstractTimedEffectPtr PlayerState::getActivePenalty() const {
    return pActivePenalty_;
}

void PlayerState::selectNextEffect() { effectSelector_->next(); }

void PlayerState::selectPrevEffect() { effectSelector_->prev(); }

void PlayerState::stashPenalty(Penalty::PenaltyType penalty) {
    stashedPenalties_->push(penalty);
}

std::queue<Penalty::PenaltyType> PlayerState::getStashedPenalties() {
    return std::move(stashedPenalties_.value());
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

    return j;
}
