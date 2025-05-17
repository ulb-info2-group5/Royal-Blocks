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

#include "timed_penalty.hpp"
#include "blackout.hpp"
#include "input_lock.hpp"
#include "reverse_controls.hpp"
#include "speed_up.hpp"

#include <iostream>
#include <memory>

TimedPenalty::TimedPenalty(PenaltyType penaltyType)
    : penaltyType_{penaltyType} {}

TimedPenaltyPtr TimedPenalty::makePenalty(PenaltyType penaltyType) {
    TimedPenaltyPtr pPenalty;

    switch (penaltyType) {
    case PenaltyType::ReverseControls:
        pPenalty = std::make_unique<ReverseControls>();
        break;
    case PenaltyType::InputLock:
        pPenalty = std::make_unique<InputLock>();
        break;
    case PenaltyType::SpeedUp:
        pPenalty = std::make_unique<SpeedUp>();
        break;
    case PenaltyType::Blackout:
        pPenalty = std::make_unique<Blackout>();
        break;
    default:
        std::cerr << "unknown timed penalty type" << std::endl;
        ;
        break;
    }

    return pPenalty;
}

PenaltyType TimedPenalty::getPenaltyType() const { return penaltyType_; }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json TimedPenalty::serialize() const {
    nlohmann::json j;

    j["penaltyType"] = getPenaltyType();
    j["elapsedTime"] = getElapsedTime();

    return j;
}
