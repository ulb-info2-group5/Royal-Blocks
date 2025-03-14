#ifndef BINDINGS_REMOVE_FRIEND_HPP
#define BINDINGS_REMOVE_FRIEND_HPP

#include "binding_type.hpp"

#include "../types/types.hpp"

#include <nlohmann/json.hpp>
namespace bindings {

    struct RemoveFriend {
        UserID userID;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::RemoveFriend},
                                  {"data",
                                   {
                                       {"playerId", userID},
                                   }}};
        }

        static RemoveFriend from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::RemoveFriend) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return RemoveFriend{
                data.at("playerId").get<UserID>(),
            };
        }
    };

} // namespace bindings

#endif // BINDINGS_REMOVE_FRIEND_HPP
