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

#include "tick_timed_effect.hpp"

TickTimedEffect::TickTimedEffect(size_t ticksNum)
    : ATimedEffect{}, numTicks_(ticksNum), remainingTicks_(ticksNum) {}

TickTimedEffect::TickTimedEffect(const TickTimedEffect &other)
    : TickTimedEffect{other.remainingTicks_} {}

bool TickTimedEffect::operator==(const TickTimedEffect &other) const {
    return remainingTicks_ == other.remainingTicks_;
}

void TickTimedEffect::tick() {
    if (remainingTicks_ > 0) {
        remainingTicks_--;
    }
}

bool TickTimedEffect::isFinished() const { return remainingTicks_ <= 0; }

double TickTimedEffect::getElapsedTime() const {
    return 1.0
           - static_cast<double>(remainingTicks_)
                 / static_cast<double>(numTicks_);
}

std::ostream &operator<<(std::ostream &os,
                         const TickTimedEffect &tickTimedEffect) {
    os << "placementTimedEffect(" << tickTimedEffect.remainingTicks_
       << " left)";
    return os;
}
