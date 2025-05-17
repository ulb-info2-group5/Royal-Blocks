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

#ifndef BLACKOUT_HPP
#define BLACKOUT_HPP

#include "../tick_timed_effect.hpp"
#include "timed_penalty.hpp"

class Blackout final : public TimedPenalty, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

  public:
    Blackout();
    Blackout(const Blackout &) = delete;
    Blackout(Blackout &&) = delete;
    Blackout &operator=(const Blackout &) = delete;
    Blackout &operator=(Blackout &&) = delete;

    ~Blackout() = default;
};

#endif // BLACKOUT_HPP
