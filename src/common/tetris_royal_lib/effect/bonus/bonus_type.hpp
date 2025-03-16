#ifndef BONUS_TYPE_HPP
#define BONUS_TYPE_HPP

#include <string>

enum class BonusType {
    SlowDown,
    MiniTetrominoes,
    NumBonusType,
};

std::string toString(BonusType type);

std::ostream &operator<<(std::ostream &os, BonusType type);

#endif // BONUS_TYPE_HPP
