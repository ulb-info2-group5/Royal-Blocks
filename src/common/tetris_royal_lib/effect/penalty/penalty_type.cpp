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

#include "penalty_type.hpp"

std::string toString(PenaltyType type) {
    switch (type) {
    case PenaltyType::Blackout:
        return "Blackout";
    case PenaltyType::InputLock:
        return "InputLock";
    case PenaltyType::Lightning:
        return "Lightning";
    case PenaltyType::ReverseControls:
        return "ReverseControls";
    case PenaltyType::SpeedUp:
        return "SpeedUp";
    default:
        return "Unknown";
    }
}

std::ostream &operator<<(std::ostream &os, PenaltyType type) {
    os << toString(type);
    return os;
}
