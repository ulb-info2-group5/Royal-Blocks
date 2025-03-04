#include "bonus_type.hpp"

std::ostream &operator<<(std::ostream &os, BonusType type) {
    switch (type) {
    case BonusType::SlowDown:
        os << "SlowDown";
        break;
    case BonusType::MiniTetrominoes:
        os << "MiniTetrominoes";
        break;
    default:
        os << "unknown";
        break;
    }
    return os;
}
