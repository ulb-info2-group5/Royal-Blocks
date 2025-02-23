#include "slow_down.hpp"
#include "timed_bonus.hpp"

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
        break;
    }

    return pBonus;
}

BonusType TimedBonus::getBonusType() const { return bonusType_; }

std::ostream &operator<<(std::ostream &os, const TimedBonus &bonus) {
    os << "Bonus(" << bonus.getBonusType() << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, BonusType type) {
    switch (type) {
    case BonusType::SlowDown:
        os << "SlowDown";
        break;
    case BonusType::MiniTetrominoes:
        os << "MiniTetrominoes";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}
