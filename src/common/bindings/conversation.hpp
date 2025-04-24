#ifndef BINDINGS_CONVERSATION_HPP
#define BINDINGS_CONVERSATION_HPP

#include "user.hpp"
#include "constants.hpp"

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

            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::Conversation},
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
