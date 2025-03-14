#ifndef BINDINGS_USER_HPP
#define BINDINGS_USER_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "../types/types.hpp"
#include "binding_type.hpp"
#include "user_state.hpp"
#include <cstddef>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace bindings {

    struct User {
        

        UserID userID;
        std::string username;
        State state;
        std::optional<GameMode> gameMode;

        bool isJoinable() const { return state == State::Matchmaking; }

        nlohmann::json to_json() const {
            nlohmann::json j_data{
                {"playerId", userID}, {"username", username}, {"state", state}};

            if (gameMode) {
                j_data["gameMode"] = gameMode.value();
            } else {
                j_data["gameMode"] = nullptr;
            }

            return nlohmann::json{{"type", BindingType::User},
                                  {"data", j_data}};
        }

        static User from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::User) {
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
