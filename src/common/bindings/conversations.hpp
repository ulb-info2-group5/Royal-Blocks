#ifndef BINDINGS_CONVERSATIONS_HPP
#define BINDINGS_CONVERSATIONS_HPP

#include "conversation.hpp"
#include "user.hpp"

#include <unordered_map>

namespace bindings {

    struct Conversations {
        std::unordered_map<User, Conversation> userConv;

        nlohmann::json to_json() const {
            nlohmann::json j_userConv = nlohmann::json::array();

            for (const auto &[user, conversation] : userConv) {
                j_userConv.push_back(
                    {user.playerId, user.username, conversation.to_json()});
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

            Conversations convs;
            const auto &j_userConv = j.at("data").at("userConv");

            for (const auto &entry : j_userConv) {
                User user{entry.at(0).get<PlayerID>(),
                          entry.at(1).get<std::string>()};
                Conversation conv = Conversation::from_json(entry.at(2));

                convs.userConv[user] = conv;
            }

            return convs;
        }
    };

} // namespace bindings

#endif // BINDINGS_CONVERSATIONS_HPP
