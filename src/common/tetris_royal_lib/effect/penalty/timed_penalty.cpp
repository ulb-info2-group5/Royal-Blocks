#include "timed_penalty.hpp"
#include "blackout.hpp"
#include "input_lock.hpp"
#include "reverse_controls.hpp"
#include "speed_up.hpp"

#include <memory>

TimedPenalty::TimedPenalty(PenaltyType penaltyType)
    : penaltyType_{penaltyType} {}

TimedPenaltyPtr TimedPenalty::makePenalty(PenaltyType penaltyType) {
    TimedPenaltyPtr pPenalty;

    switch (penaltyType) {
    case PenaltyType::ReverseControls:
        pPenalty = std::make_unique<ReverseControls>();
        break;
    case PenaltyType::InputLock:
        pPenalty = std::make_unique<InputLock>();
        break;
    case PenaltyType::SpeedUp:
        pPenalty = std::make_unique<SpeedUp>();
        break;
    case PenaltyType::Blackout:
        pPenalty = std::make_unique<Blackout>();
        break;
    default:
        break;
    }

    return pPenalty;
}

PenaltyType TimedPenalty::getPenaltyType() const { return penaltyType_; }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json TimedPenalty::serialize() const {
    nlohmann::json j;

    j["penaltyType"] = getPenaltyType();
    j["elapsedTime"] = getElapsedTime();

    return j;
}
