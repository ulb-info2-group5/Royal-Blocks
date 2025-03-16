#include "bonus_type.hpp"

std::string toString(BonusType type) {
    switch (type) {
    case BonusType::SlowDown:
        return "SlowDown";
    case BonusType::MiniTetrominoes:
        return "MiniTetrominoes";
    default:
        return "unknown";
    }
}

std::ostream &operator<<(std::ostream &os, BonusType type) {
    os << toString(type);
    return os;
}
