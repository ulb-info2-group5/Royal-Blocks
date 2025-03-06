#ifndef BINDINGS_MESSAGE_HPP
#define BINDINGS_MESSAGE_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

using PlayerID = size_t;

namespace bindings {

    struct Message {
        PlayerID recipientId;
        std::string content;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::Message},
                                  {"data",
                                   {
                                       {"recipientId", recipientId},
                                       {"content", content},
                                   }}};
        }

        static Message from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Message) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Message{data.at("recipientId").get<PlayerID>(),
                           data.at("content").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_MESSAGE_HPP
