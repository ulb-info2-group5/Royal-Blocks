#include "penalty.hpp"
#include "blackout.hpp"
#include "input_lock.hpp"
#include "reverse_controls.hpp"
#include "speed_up.hpp"

#include <memory>

Penalty::Penalty(PenaltyType penaltyType) : penaltyType_{penaltyType} {}

PenaltyPtr Penalty::makePenalty(PenaltyType penaltyType) {
    PenaltyPtr pPenalty;

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

Penalty::PenaltyType Penalty::getPenaltyType() const { return penaltyType_; }

std::ostream &operator<<(std::ostream &os, Penalty::PenaltyType type) {
    switch (type) {
    case Penalty::PenaltyType::Blackout:
        os << "Blackout";
        break;
    case Penalty::PenaltyType::InputLock:
        os << "InputLock";
        break;
    case Penalty::PenaltyType::Lightning:
        os << "Lightning";
        break;
    case Penalty::PenaltyType::ReverseControls:
        os << "ReverseControls";
        break;
    case Penalty::PenaltyType::SpeedUp:
        os << "SpeedUp";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}
