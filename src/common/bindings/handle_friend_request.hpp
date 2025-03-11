#ifndef BINDINGS_HANDLE_FRIEND_REQUEST_HPP
#define BINDINGS_HANDLE_FRIEND_REQUEST_HPP

#include "user.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct HandleFriendRequest {
        enum class Action { Accept, Decline };

        User user;
        Action action;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::HandleFriendRequest},
                                  {"data",
                                   {
                                       {"user", user.to_json()},
                                       {"action", action},
                                   }}};
        }

        static HandleFriendRequest from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::HandleFriendRequest) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return HandleFriendRequest{
                User::from_json(data.at("user")),
                data.at("action").get<Action>(),
            };
        }
    };

} // namespace bindings

#endif // BINDINGS_HANDLE_FRIEND_REQUEST_HPP
