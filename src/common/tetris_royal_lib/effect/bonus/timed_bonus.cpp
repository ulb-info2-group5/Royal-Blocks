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

#include "timed_bonus.hpp"
#include "nlohmann/json_fwd.hpp"
#include "slow_down.hpp"

#include <memory>

#include <iostream>

TimedBonus::TimedBonus(BonusType bonusType) : bonusType_(bonusType) {}

TimedBonusPtr TimedBonus::makeBonus(BonusType bonusType) {
    TimedBonusPtr pBonus;

    switch (bonusType) {
    case BonusType::SlowDown:
        pBonus = std::make_unique<SlowDown>();
        break;
    default:
        std::cerr << "unknown timed bonus type" << std::endl;
        break;
    }

    return pBonus;
}

BonusType TimedBonus::getBonusType() const { return bonusType_; }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json TimedBonus::serialize() const {
    nlohmann::json j;

    j["bonusType"] = getBonusType();
    j["elapsedTime"] = getElapsedTime();

    return j;
}
