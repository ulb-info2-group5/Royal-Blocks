#ifndef BINDINGS_USER_HPP
#define BINDINGS_USER_HPP

#include "binding_type.hpp"

#include <cstddef>
#include <string>

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct User {
        PlayerID playerId;
        std::string username;
        bool online;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::User},
                                  {"data",
                                   {
                                       {"playerId", playerId},
                                       {"username", username},
                                       {"online", online},
                                   }}};
        }

        static User from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::User) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return User{data.at("playerId").get<PlayerID>(),
                        data.at("username").get<std::string>(),
                        data.at("online").get<bool>()};
        }

        bool operator==(const User &other) const {
            return playerId == other.playerId;
        }
    };

} // namespace bindings

namespace std {
    template <> struct hash<bindings::User> {
        std::size_t operator()(const bindings::User &user) const noexcept {
            return std::hash<PlayerID>{}(user.playerId);
        }
    };
} // namespace std

#endif // BINDINGS_USER_HPP
