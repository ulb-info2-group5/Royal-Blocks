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

#ifndef BINDINGS_CONVERSATIONS_HPP
#define BINDINGS_CONVERSATIONS_HPP

#include "constants.hpp"
#include "conversation.hpp"
#include "user.hpp"

#include <unordered_map>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Represents multiple conversations associated with a specific user.
     */
    struct Conversations {
        using NameConversation = std::pair<std::string, Conversation>;

        std::unordered_map<UserID, NameConversation> conversationsById;

        nlohmann::json to_json() const {
            nlohmann::json j_userConv = nlohmann::json::array();

            for (const auto &[userID, nameWithConversation] :
                 conversationsById) {
                const auto &[name, conversation] = nameWithConversation;
                j_userConv.push_back({userID, name, conversation.to_json()});
            }

            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::Conversations},
                {"data",
                 {
                     {"userConv", j_userConv},
                 }}};
        }

        static Conversations from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::Conversations) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            Conversations conversations;

            for (const auto &entry : j.at("data").at("userConv")) {
                UserID userID = entry.at(0).get<UserID>();
                std::string name = entry.at(1).get<std::string>();
                Conversation conversation =
                    Conversation::from_json(entry.at(2));

                conversations.conversationsById[userID] =
                    std::make_pair(std::move(name), std::move(conversation));
            }

            return conversations;
        }
    };

} // namespace bindings

#endif // BINDINGS_CONVERSATIONS_HPP
