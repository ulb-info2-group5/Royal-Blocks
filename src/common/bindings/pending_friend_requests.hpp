#ifndef BINDINGS_PENDING_FRIEND_REQUESTS_HPP
#define BINDINGS_PENDING_FRIEND_REQUESTS_HPP

#include "nlohmann/json_fwd.hpp"
#include "user.hpp"
#include <vector>

namespace bindings {

    struct PendingFriendRequests {
        std::vector<bindings::User> requests;

        nlohmann::json to_json() const {
            nlohmann::json j_requests = nlohmann::json::array();
            for (const User &requester : requests) {
                j_requests.push_back(requester.to_json());
            }

            return nlohmann::json{{"type", BindingType::PendingFriendRequests},
                                  {"data",
                                   {
                                       {"requests", j_requests},
                                   }}};
        }

        static PendingFriendRequests from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::PendingFriendRequests) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            PendingFriendRequests pendingFriendRequests{};

            const auto &data = j.at("data");
            for (auto &j_requester : data.at("requests")) {
                pendingFriendRequests.requests.push_back(
                    bindings::User::from_json(j_requester));
            }

            return pendingFriendRequests;
        }
    };

} // namespace bindings

#endif // BINDINGS_PENDING_FRIEND_REQUESTS_HPP
