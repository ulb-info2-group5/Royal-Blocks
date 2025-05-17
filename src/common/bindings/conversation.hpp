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

#ifndef BINDINGS_CONVERSATION_HPP
#define BINDINGS_CONVERSATION_HPP

#include "constants.hpp"
#include "user.hpp"

#include <vector>

using SenderMessage = std::pair<UserID, std::string>;

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding representing a single conversation between two players.
     */
    struct Conversation {
        std::vector<SenderMessage> senderMessages;

        nlohmann::json to_json() const {
            nlohmann::json j_senderMessages = nlohmann::json::array();

            for (const SenderMessage &senderMessage : senderMessages) {
                j_senderMessages.push_back(senderMessage);
            }

            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::Conversation},
                {"data",
                 {
                     {"senderMessages", j_senderMessages},
                 }}};
        }

        static Conversation from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::Conversation) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            Conversation conversation;

            const auto &data = j.at("data");

            for (const auto &j_senderMsg : data.at("senderMessages")) {
                conversation.senderMessages.push_back(
                    j_senderMsg.get<SenderMessage>());
            }

            return conversation;
        }
    };

} // namespace bindings

#endif // BINDINGS_CONVERSATION_HPP
