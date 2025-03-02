#ifndef BONUS_TYPE_HPP
#define BONUS_TYPE_HPP

#include <ostream>

enum class BonusType {
    SlowDown,
    MiniTetrominoes,
    NumBonusType,
};

std::ostream &operator<<(std::ostream &os, BonusType type);

#endif // BONUS_TYPE_HPP
