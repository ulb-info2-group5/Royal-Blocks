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

#ifndef BONUS_HPP
#define BONUS_HPP

#include <memory>
#include <nlohmann/json_fwd.hpp>

#include "../abstract_timed_effect.hpp"
#include "bonus_type.hpp"

class BonusTest;

class TimedBonus;
using TimedBonusPtr = std::shared_ptr<TimedBonus>;

class TimedBonus : public virtual ATimedEffect {
  private:
    BonusType bonusType_;

  protected:
    TimedBonus(BonusType bonusType);
    TimedBonus(const TimedBonus &) = default;
    TimedBonus(TimedBonus &&) = default;
    TimedBonus &operator=(const TimedBonus &) = delete;
    TimedBonus &operator=(TimedBonus &&) = delete;

  public:
    virtual ~TimedBonus() = default;

    /**
     * @brief Creates a new Bonus instance.
     */
    static TimedBonusPtr makeBonus(BonusType bonusType);

    /**
     * @brief Returns the bonus's type.
     */
    BonusType getBonusType() const;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the bonus to json.
     */
    nlohmann::json serialize() const;

    friend BonusTest;
};

#endif // BONUS_HPP
