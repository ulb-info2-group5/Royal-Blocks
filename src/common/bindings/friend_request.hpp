#ifndef BINDINGS_FRIEND_REQUEST_HPP
#define BINDINGS_FRIEND_REQUEST_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct FriendRequest {
        std::string targetName;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::FriendRequest},
                                  {"data",
                                   {
                                       {"targetName", targetName},
                                   }}};
        }

        static FriendRequest from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::FriendRequest) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return FriendRequest{
                data.at("targetName").get<std::string>(),
            };
        }
    };

} // namespace bindings

#endif // BINDINGS_FRIEND_REQUEST_HPP
