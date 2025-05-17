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

#ifndef BINDINGS_FRIENDS_LIST_HPP
#define BINDINGS_FRIENDS_LIST_HPP

#include "binding_type.hpp"
#include "user.hpp"

#include "constants.hpp"

#include <nlohmann/json.hpp>

#include <vector>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding containing a user's friendslist.
     */
    struct FriendsList {
        std::vector<User> friendsList;

        nlohmann::json to_json() const {
            nlohmann::json j_friendsList = nlohmann::json::array();

            for (const User &user : friendsList) {
                j_friendsList.push_back(user.to_json());
            }

            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::FriendsList},
                                  {"data",
                                   {
                                       {"friendsList", j_friendsList},
                                   }}};
        }

        static FriendsList from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::FriendsList) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &j_friendsList = j.at("data").at("friendsList");
            std::vector<User> friends;
            friends.reserve(j_friendsList.size());

            for (const auto &j_user : j_friendsList) {
                friends.push_back(User::from_json(j_user));
            }

            return FriendsList{std::move(friends)};
        }
    };

} // namespace bindings

#endif // BINDINGS_FRIENDS_LIST_HPP
