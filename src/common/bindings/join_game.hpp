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

#ifndef BINDINGS_JOIN_FRIEND_HPP
#define BINDINGS_JOIN_FRIEND_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "../tetris_royal_lib/player_state/player_state.hpp"
#include "constants.hpp"
#include "in_game/select_target.hpp"

#include <nlohmann/json.hpp>
#include <optional>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @biref Binding sent by the client to join a game.
     */
    struct JoinGame {
        // friendId = nullopt means "join any game in this GameMode"
        GameMode gameMode;
        std::optional<UserID> friendId;

        nlohmann::json to_json() const {
            nlohmann::json j_data;

            j_data["gameMode"] = gameMode;

            if (friendId) {
                j_data["friendId"] = friendId.value();
            } else {
                j_data["friendId"] = nullptr;
            }

            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::JoinGame},
                                  {"data", j_data}};
        }

        static JoinGame from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::JoinGame) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");

            return JoinGame{
                data.at("gameMode").get<GameMode>(),

                data.at("friendId").is_null()
                    ? std::nullopt
                    : std::make_optional(data.at("friendId").get<UserID>())};
        }
    };

} // namespace bindings

#endif // BINDINGS_JOIN_FRIEND_HPP
