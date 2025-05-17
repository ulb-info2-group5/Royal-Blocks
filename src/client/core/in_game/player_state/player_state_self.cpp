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

#include "player_state_self.hpp"

#include <map>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>
#include <optional>
#include <queue>

#include "../../../../common/types/types.hpp"
#include "core/in_game/effects/timed_bonus.hpp"
#include "core/in_game/effects/timed_penalty.hpp"

void client::PlayerStateSelf::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(userID);
    j.at("score").get_to(score);
    j.at("isAlive").get_to(isAlive);
    j.at("username").get_to(username);

    if (!j.at("penaltyTarget").is_null()) {
        penaltyTarget = std::make_optional(UserID{});
        penaltyTarget = j.at("penaltyTarget").get<UserID>();
    } else {
        penaltyTarget = std::nullopt;
    }

    if (!j.at("energy").is_null()) {
        energy = std::make_optional(Energy{});
        energy = j.at("energy").get<Energy>();
    } else {
        energy = std::nullopt;
    }

    for (auto &penalty : j.at("stashedPenalties")) {
        stashedPenalties.push(penalty);
    }

    if (!j.at("activeBonus").is_null()) {
        activeBonus = std::make_optional(client::TimedBonus{});
        activeBonus->deserialize(j.at("activeBonus"));
    } else {
        activeBonus = std::nullopt;
    }

    if (!j.at("activePenalty").is_null()) {
        activePenalty = std::make_optional(client::TimedPenalty{});
        activePenalty->deserialize(j.at("activePenalty"));
    } else {
        activePenalty = std::nullopt;
    }
}
