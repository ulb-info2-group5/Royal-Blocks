#ifndef PENALTY_TYPE_HPP
#define PENALTY_TYPE_HPP

#include <string>

enum class PenaltyType {
    ReverseControls,
    InputLock,
    SpeedUp,
    Lightning,
    Blackout,
    NumPenaltyType,
};

/**
 * @brief Converts the given PenaltyType to a string.
 */
std::string toString(PenaltyType type);

std::ostream &operator<<(std::ostream &os, PenaltyType type);

#endif // PENALTY_TYPE_HPP
