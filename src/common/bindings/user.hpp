#ifndef BINDINGS_USER_HPP
#define BINDINGS_USER_HPP

#include "binding_type.hpp"

#include <cstddef>
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

        bool isJoinable() const { return state == State::Matchmaking; }

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::User},
                                  {"data",
                                   {
                                       {"playerId", playerId},
                                       {"username", username},
                                       {"state", state},
                                   }}};
        }

        static User from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::User) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return User{data.at("playerId").get<PlayerID>(),
                        data.at("username").get<std::string>(),
                        data.at("state").get<State>()};
        }

        bool operator==(const User &other) const {
            return playerId == other.playerId;
        }
    };

} // namespace bindings

#endif // BINDINGS_USER_HPP
