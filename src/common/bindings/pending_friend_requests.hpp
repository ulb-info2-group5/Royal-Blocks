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

#ifndef BINDINGS_PENDING_FRIEND_REQUESTS_HPP
#define BINDINGS_PENDING_FRIEND_REQUESTS_HPP

#include "constants.hpp"
#include "nlohmann/json_fwd.hpp"
#include "user.hpp"
#include <vector>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the server, contains all the pending friends
     * request.
     */
    struct PendingFriendRequests {
        std::vector<bindings::User> requests;

        nlohmann::json to_json() const {
            nlohmann::json j_requests = nlohmann::json::array();
            for (const User &requester : requests) {
                j_requests.push_back(requester.to_json());
            }

            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::PendingFriendRequests},
                {"data",
                 {
                     {"requests", j_requests},
                 }}};
        }

        static PendingFriendRequests from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::PendingFriendRequests) {
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
