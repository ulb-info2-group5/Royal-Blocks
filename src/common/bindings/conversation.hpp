#ifndef BINDINGS_CONVERSATION_HPP
#define BINDINGS_CONVERSATION_HPP

#include "user.hpp"

#include <vector>

using SenderMessage = std::pair<UserID, std::string>;

namespace bindings {

    struct Conversation {
        std::vector<SenderMessage> senderMessages;

        nlohmann::json to_json() const {
            nlohmann::json j_senderMessages = nlohmann::json::array();

            for (const SenderMessage &senderMessage : senderMessages) {
                j_senderMessages.push_back(senderMessage);
            }

            return nlohmann::json{{"type", BindingType::Conversation},
                                  {"data",
                                   {
                                       {"senderMessages", j_senderMessages},
                                   }}};
        }

        static Conversation from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Conversation) {
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
