#ifndef BINDINGS_CONVERSATIONS_HPP
#define BINDINGS_CONVERSATIONS_HPP

#include "conversation.hpp"
#include "user.hpp"

#include <unordered_map>

namespace bindings {

    struct Conversations {
        using NameConversation = std::pair<std::string, Conversation>;

        std::unordered_map<PlayerID, NameConversation> conversationsById;

        nlohmann::json to_json() const {
            nlohmann::json j_userConv = nlohmann::json::array();

            for (const auto &[playerId, nameWithConversation] :
                 conversationsById) {
                const auto &[name, conversation] = nameWithConversation;
                j_userConv.push_back({playerId, name, conversation.to_json()});
            }

            return nlohmann::json{{"type", BindingType::Conversations},
                                  {"data",
                                   {
                                       {"userConv", j_userConv},
                                   }}};
        }

        static Conversations from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Conversations) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            Conversations conversations;

            for (const auto &entry : j.at("data").at("userConv")) {
                PlayerID playerId = entry.at(0).get<PlayerID>();
                std::string name = entry.at(1).get<std::string>();
                Conversation conversation =
                    Conversation::from_json(entry.at(2));

                conversations.conversationsById[playerId] =
                    std::make_pair(std::move(name), std::move(conversation));
            }

            return conversations;
        }
    };

} // namespace bindings

#endif // BINDINGS_CONVERSATIONS_HPP
