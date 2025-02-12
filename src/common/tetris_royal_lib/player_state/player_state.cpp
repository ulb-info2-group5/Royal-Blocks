#include "player_state.hpp"

#include <optional>

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

    grantedBonusesQueue_.value().pushBack(bonus);
}

void PlayerState::receivePenalty(Penalty::PenaltyType penalty) {
    if (!receivedPenaltiesQueue_.has_value()) {
        return;
    }

    receivedPenaltiesQueue_.value().pushBack(penalty);
}

std::optional<Bonus::BonusType> PlayerState::fetchGrantedBonus() {
    return grantedBonusesQueue_.and_then(
        [](auto &queue) { return queue.popFront(); });
}

std::optional<Penalty::PenaltyType> PlayerState::fetchReceivedPenalty() {
    return receivedPenaltiesQueue_.and_then(
        [](auto &queue) { return queue.popFront(); });
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

void PlayerState::selectNextEffect() { effectSelector_->next(); }

void PlayerState::selectPrevEffect() { effectSelector_->prev(); }
