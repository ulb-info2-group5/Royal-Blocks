#include "player_state.hpp"
#include "../effect/bonus/bonus_type.hpp"
#include "../effect/penalty/speed_up.hpp"

#include <optional>

PlayerState::PlayerState(UserID userID, std::string username, Score score)
    : TetrisObserver{}, userID_{userID}, score_{score}, isAlive_{true},

      username{username.empty() ? std::string{DEFAULT_USERNAME_PREFIX}
                                      + std::to_string(userID)
                                : username},

      penaltyTarget_{std::nullopt}, energy_{std::nullopt},
      receivedPenaltiesQueue_{}, grantedBonusesQueue_{}, pActiveBonus_{nullptr},
      pActivePenalty_{nullptr}, engineTicksSinceLastTick_{0} {}

void PlayerState::toggleEffects(bool activated) {
    energy_ = activated ? std::make_optional<Energy>(0) : std::nullopt;
}

UserID PlayerState::getUserID() const { return userID_; }

Score PlayerState::getScore() const { return score_; }

void PlayerState::increaseScore(Score val) { score_ += val; }

bool PlayerState::isAlive() const { return isAlive_; }

void PlayerState::setAlive(bool isAlive) { isAlive_ = isAlive; }

std::optional<UserID> PlayerState::getPenaltyTarget() const {
    return penaltyTarget_;
}

void PlayerState::setPenaltyTarget(UserID userID) { penaltyTarget_ = userID; }

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

void PlayerState::grantBonus(BonusType bonus) {
    grantedBonusesQueue_.push(bonus);
}

void PlayerState::receivePenalty(PenaltyType penalty) {
    receivedPenaltiesQueue_.push(penalty);
}

std::optional<BonusType> PlayerState::fetchGrantedBonus() {
    std::optional<BonusType> ret;

    if (grantedBonusesQueue_.empty()) {
        ret = std::nullopt;
    } else {
        ret = grantedBonusesQueue_.front();
        grantedBonusesQueue_.pop();
    }

    return ret;
}

std::optional<PenaltyType> PlayerState::fetchReceivedPenalty() {
    std::optional<PenaltyType> ret;

    if (receivedPenaltiesQueue_.empty()) {
        ret = std::nullopt;
    } else {
        ret = receivedPenaltiesQueue_.front();
        receivedPenaltiesQueue_.pop();
    }

    return ret;
}

void PlayerState::setActivePenalty(const TimedPenaltyPtr &pTimedPenalty) {
    pActivePenalty_ = pTimedPenalty;
}

void PlayerState::setActiveBonus(const TimedBonusPtr &pTimedBonus) {
    pActiveBonus_ = pTimedBonus;
}

TimedBonusPtr &PlayerState::getActiveBonus() { return pActiveBonus_; }

TimedPenaltyPtr &PlayerState::getActivePenalty() { return pActivePenalty_; }

const TimedBonusPtr &PlayerState::getActiveBonus() const {
    return pActiveBonus_;
}

const TimedPenaltyPtr &PlayerState::getActivePenalty() const {
    return pActivePenalty_;
}

void PlayerState::stashPenalty(PenaltyType penalty) {
    stashedPenalties_.push_back(penalty);
}

std::deque<PenaltyType> PlayerState::getStashedPenalties() {
    return stashedPenalties_;
    stashedPenalties_.clear();
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
    j["playerID"] = userID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;
    j["username"] = username;

    return j;
}

nlohmann::json PlayerState::serializeSelf() const {
    nlohmann::json j;
    j["playerID"] = userID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;
    j["username"] = username;

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

    nlohmann::json j_stashedPenalties = nlohmann::json::array();
    for (const auto &stashedPenalty : stashedPenalties_) {
        j_stashedPenalties.push_back(stashedPenalty);
    }
    j["stashedPenalties"] = j_stashedPenalties;

    if (pActiveBonus_) {
        j["activeBonus"] = pActiveBonus_->serialize();
    } else {
        j["activeBonus"] = nullptr;
    }

    if (pActivePenalty_) {
        j["activePenalty"] = pActivePenalty_->serialize();
    } else {
        j["activePenalty"] = nullptr;
    }

    return j;
}
