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

#ifndef TIMED_BONUS_HPP
#define TIMED_BONUS_HPP

#include "abstract_timed_effect.hpp"
#include "nlohmann/json_fwd.hpp"

enum class BonusType;

namespace client {

    /**
     * @brief Timed bonus class.
     */
    struct TimedBonus final : public client::AbstractTimedEffect {
        BonusType bonusType;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // TIMED_BONUS_HPP
