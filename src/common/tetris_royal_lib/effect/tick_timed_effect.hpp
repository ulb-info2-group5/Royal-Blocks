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

#ifndef TICK_TIMED_EFFECT_HPP
#define TICK_TIMED_EFFECT_HPP

#include "abstract_timed_effect.hpp"

#include <cstddef>
#include <ostream>

class TickTimedEffectTest;

class TickTimedEffect : public virtual ATimedEffect {
  private:
    size_t numTicks_;
    // Number of ticks left before the effect expires
    // (decreases each tick)
    size_t remainingTicks_;

  protected:
    TickTimedEffect(size_t ticksNum);
    TickTimedEffect(const TickTimedEffect &);
    TickTimedEffect(TickTimedEffect &&) = delete;
    TickTimedEffect &operator=(const TickTimedEffect &) = delete;
    TickTimedEffect &operator=(TickTimedEffect &&) = delete;

  public:
    virtual ~TickTimedEffect() = default;

    bool operator==(const TickTimedEffect &other) const;

    void tick() override;

    bool isFinished() const override;

    double getElapsedTime() const override;

    /**
     * @brief Outputs the TickTimedEffect to a stream.
     *
     * @param os The output stream.
     * @param TicktTimedEffect The TickTimedEffect to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const TickTimedEffect &tickTimedEffect);

    friend TickTimedEffectTest;
};

#endif // TICK_TIMED_EFFECT_HPP
