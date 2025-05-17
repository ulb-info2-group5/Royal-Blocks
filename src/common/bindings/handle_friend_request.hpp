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

#ifndef BINDINGS_HANDLE_FRIEND_REQUEST_HPP
#define BINDINGS_HANDLE_FRIEND_REQUEST_HPP

#include "constants.hpp"
#include "user.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to handle a friend request (accept or
     * decline it).
     */
    struct HandleFriendRequest {
        enum class Action { Accept, Decline };

        UserID userId;
        Action action;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::HandleFriendRequest},
                {"data",
                 {
                     {"user", userId},
                     {"action", action},
                 }}};
        }

        static HandleFriendRequest from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::HandleFriendRequest) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return HandleFriendRequest{
                data.at("user").get<UserID>(),
                data.at("action").get<Action>(),
            };
        }
    };

} // namespace bindings

#endif // BINDINGS_HANDLE_FRIEND_REQUEST_HPP
