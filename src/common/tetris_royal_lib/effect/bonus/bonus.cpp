#include "bonus.hpp"
#include "mini_tetrominoes.hpp"
#include "slow_down.hpp"

#include <memory>

#include <iostream>

Bonus::Bonus(BonusType bonusType) : bonusType_(bonusType) {}

BonusPtr Bonus::makeBonus(BonusType bonusType) {
    BonusPtr pBonus;

    switch (bonusType) {
    case BonusType::MiniTetrominoes:
        pBonus = std::make_unique<MiniTetrominoes>();
        break;
    case BonusType::SlowDown:
        pBonus = std::make_unique<SlowDown>();
        break;
    default:
        break;
    }

    return pBonus;
}

Bonus::BonusType Bonus::getBonusType() const { return bonusType_; }

std::ostream &operator<<(std::ostream &os, const Bonus &bonus) {
    os << "Bonus(" << bonus.getBonusType() << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, Bonus::BonusType type) {
    switch (type) {
    case Bonus::BonusType::SlowDown:
        os << "SlowDown";
        break;
    case Bonus::BonusType::MiniTetrominoes:
        os << "MiniTetrominoes";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}
