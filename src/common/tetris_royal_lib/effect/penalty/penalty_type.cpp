#include "penalty_type.hpp"

std::string toString(PenaltyType type) {
    switch (type) {
    case PenaltyType::Blackout:
        return "Blackout";
    case PenaltyType::InputLock:
        return "InputLock";
    case PenaltyType::Lightning:
        return "Lightning";
    case PenaltyType::ReverseControls:
        return "ReverseControls";
    case PenaltyType::SpeedUp:
        return "SpeedUp";
    default:
        return "Unknown";
    }
}

std::ostream &operator<<(std::ostream &os, PenaltyType type) {
    os << toString(type);
    return os;
}
