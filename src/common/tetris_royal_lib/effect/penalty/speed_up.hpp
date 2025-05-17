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

#ifndef SPEED_UP_HPP
#define SPEED_UP_HPP

#include "../tick_timed_effect.hpp"
#include "timed_penalty.hpp"

class SpeedUp final : public TimedPenalty, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

  public:
    static constexpr size_t SpeedUpFactor = 2;

    SpeedUp();
    SpeedUp(const SpeedUp &) = delete;
    SpeedUp(SpeedUp &&) = delete;
    SpeedUp &operator=(const SpeedUp &) = delete;
    SpeedUp &operator=(SpeedUp &&) = delete;

    ~SpeedUp() = default;
};

#endif // SPEED_UP_HPP
