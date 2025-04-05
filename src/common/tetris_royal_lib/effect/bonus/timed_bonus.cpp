#include "timed_bonus.hpp"
#include "nlohmann/json_fwd.hpp"
#include "slow_down.hpp"

#include <memory>

#include <iostream>

TimedBonus::TimedBonus(BonusType bonusType) : bonusType_(bonusType) {}

TimedBonusPtr TimedBonus::makeBonus(BonusType bonusType) {
    TimedBonusPtr pBonus;

    switch (bonusType) {
    case BonusType::SlowDown:
        pBonus = std::make_unique<SlowDown>();
        break;
    default:
        std::cerr << "unknown timed bonus type" << std::endl;
        break;
    }

    return pBonus;
}

BonusType TimedBonus::getBonusType() const { return bonusType_; }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json TimedBonus::serialize() const {
    nlohmann::json j;

    j["bonusType"] = getBonusType();
    j["elapsedTime"] = getElapsedTime();

    return j;
}
