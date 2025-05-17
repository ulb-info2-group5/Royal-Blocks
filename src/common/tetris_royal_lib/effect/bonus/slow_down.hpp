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

#ifndef SLOW_DOWN_HPP
#define SLOW_DOWN_HPP

#include "../tick_timed_effect.hpp"
#include "timed_bonus.hpp"

#include <cstddef>

class SlowDown final : public TimedBonus, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

    static constexpr size_t SLOW_DOWN_FACTOR = 2;

  public:
    SlowDown();
    SlowDown(const SlowDown &) = delete;
    SlowDown(SlowDown &&) = delete;
    SlowDown &operator=(const SlowDown &) = delete;
    SlowDown &operator=(SlowDown &&) = delete;

    ~SlowDown() = default;

    /**
     * @brief Returns true if the engine tick should be ignored for the player
     * that has this effect.
     */
    bool shouldIgnoreTick();
};

#endif // SLOW_DOWN_HPP
