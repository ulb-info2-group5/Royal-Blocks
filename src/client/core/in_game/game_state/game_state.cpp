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

#include "game_state.hpp"

#include "../../../../common/types/types.hpp"
#include "core/in_game/player_tetris/player_tetris_external.hpp"
#include "core/in_game/player_tetris/player_tetris_self.hpp"
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>
#include <utility>
#include <vector>

enum class BonusType;
enum class PenaltyType;

void client::GameState::deserialize(const nlohmann::json &j) {
    self.deserialize(j.at("self"));

    isFinished = j.at("isFinished");
    gameMode = j.at("gameMode");

    for (const auto &external : j.at("externals")) {
        PlayerTetrisExternal externalPlayer;
        externalPlayer.deserialize(external);
        externals.push_back(externalPlayer);
    }

    for (const std::pair<BonusType, Energy> bonusTypePrice :
         j.at("bonusToPrice")) {
        effectsPrice.push_back(bonusTypePrice);
    }
    for (const std::pair<PenaltyType, Energy> penaltyTypePrice :
         j.at("penaltyToPrice")) {
        effectsPrice.push_back(penaltyTypePrice);
    }
}
