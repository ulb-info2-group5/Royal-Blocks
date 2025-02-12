#include "placement_timed_effect.hpp"

PlacementTimedEffect::PlacementTimedEffect(size_t placementsNum)
    : AbstractTimedEffect(), remainingPlacements_(placementsNum) {}

PlacementTimedEffect::PlacementTimedEffect(const PlacementTimedEffect &other)
    : PlacementTimedEffect{other.remainingPlacements_} {}

bool PlacementTimedEffect::operator==(const PlacementTimedEffect &other) const {
    return remainingPlacements_ == other.remainingPlacements_;
}

void PlacementTimedEffect::tetrominoPlaced() { remainingPlacements_--; }

bool PlacementTimedEffect::isFinished() const {
    return remainingPlacements_ <= 0;
}

std::ostream &operator<<(std::ostream &os,
                         const PlacementTimedEffect &placementTimedEffect) {
    os << "placementTimedEffect(" << placementTimedEffect.remainingPlacements_
       << " left)";
    return os;
}
