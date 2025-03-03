#include "penalty_type.hpp"

std::ostream &operator<<(std::ostream &os, PenaltyType type) {
    switch (type) {
    case PenaltyType::Blackout:
        os << "Blackout";
        break;
    case PenaltyType::InputLock:
        os << "InputLock";
        break;
    case PenaltyType::Lightning:
        os << "Lightning";
        break;
    case PenaltyType::ReverseControls:
        os << "ReverseControls";
        break;
    case PenaltyType::SpeedUp:
        os << "SpeedUp";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}
