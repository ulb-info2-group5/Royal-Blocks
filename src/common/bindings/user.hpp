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

#ifndef BINDINGS_USER_HPP
#define BINDINGS_USER_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "../types/types.hpp"
#include "binding_type.hpp"
#include "constants.hpp"
#include "user_state.hpp"

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Represents a user.
     */
    struct User {
        UserID userID;
        std::string username;
        State state;
        std::optional<GameMode> gameMode;

        User() = default;

        User(UserID USERID, std::string USERNAME, State STATE,
             std::optional<GameMode> GAMEMODE = std::nullopt)
            : userID(USERID), username(USERNAME), state(STATE),
              gameMode(GAMEMODE) {}

        bool isJoinable() const { return state == State::Matchmaking; }

        nlohmann::json to_json() const {
            nlohmann::json j_data{
                {"playerId", userID}, {"username", username}, {"state", state}};

            if (gameMode) {
                j_data["gameMode"] = gameMode.value();
            } else {
                j_data["gameMode"] = nullptr;
            }

            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::User},
                                  {"data", j_data}};
        }

        static User from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::User) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");

            return User{
                data.at("playerId").get<UserID>(),
                data.at("username").get<std::string>(),
                data.at("state").get<State>(),

                data.at("gameMode").is_null()
                    ? std::nullopt
                    : std::make_optional(data.at("gameMode").get<GameMode>())};
        };
    };

}; // namespace bindings

#endif // BINDINGS_USER_HPP
