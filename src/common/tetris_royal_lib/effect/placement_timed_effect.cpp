/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "placement_timed_effect.hpp"

PlacementTimedEffect::PlacementTimedEffect(size_t placementsNum)
    : ATimedEffect{}, numPlacements_(placementsNum),
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
