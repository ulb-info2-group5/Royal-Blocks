#ifndef PENALTY_TYPE_HPP
#define PENALTY_TYPE_HPP

#include <ostream>

enum class PenaltyType {
    ReverseControls,
    InputLock,
    SpeedUp,
    Lightning,
    Blackout,
    NumPenaltyType,
};

std::ostream &operator<<(std::ostream &os, PenaltyType type);

#endif // PENALTY_TYPE_HPP
