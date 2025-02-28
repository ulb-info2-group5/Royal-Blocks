#include "placement_timed_effect.hpp"

PlacementTimedEffect::PlacementTimedEffect(size_t placementsNum)
    : AbstractTimedEffect(), numPlacements_(placementsNum),
      remainingPlacements_(placementsNum) {}

PlacementTimedEffect::PlacementTimedEffect(const PlacementTimedEffect &other)
    : PlacementTimedEffect{other.remainingPlacements_} {}

bool PlacementTimedEffect::operator==(const PlacementTimedEffect &other) const {
    return remainingPlacements_ == other.remainingPlacements_;
}

void PlacementTimedEffect::tetrominoPlaced() {
    if (remainingPlacements_ > 0) {
        remainingPlacements_--;
    }
}

bool PlacementTimedEffect::isFinished() const {
    return remainingPlacements_ <= 0;
}

double PlacementTimedEffect::getElapsedTime() const {
    return 1.0
           - static_cast<double>(remainingPlacements_)
                 / static_cast<double>(numPlacements_);
}

std::ostream &operator<<(std::ostream &os,
                         const PlacementTimedEffect &placementTimedEffect) {
    os << "placementTimedEffect(" << placementTimedEffect.remainingPlacements_
       << " left)";
    return os;
}
