#ifndef BINDINGS_USER_HPP
#define BINDINGS_USER_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "binding_type.hpp"

#include <cstddef>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct User {
        enum class State {
            Offline,
            Menu,
            Matchmaking,
            InGame,
        };

        PlayerID playerId;
        std::string username;
        State state;
        std::optional<GameMode> gameMode;

        bool isJoinable() const { return state == State::Matchmaking; }

        nlohmann::json to_json() const {
            nlohmann::json j_data{{"playerId", playerId},
                                  {"username", username},
                                  {"state", state}};

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
                data.at("playerId").get<PlayerID>(),
                data.at("username").get<std::string>(),
                data.at("state").get<State>(),

                data.at("gameMode").is_null()
                    ? std::nullopt
                    : std::make_optional(data.at("gameMode").get<GameMode>())};
        };
    };

}; // namespace bindings

#endif // BINDINGS_USER_HPP
