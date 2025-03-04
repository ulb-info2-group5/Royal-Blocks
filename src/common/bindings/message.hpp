#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <nlohmann/json.hpp>
#include <string>

using PlayerID = size_t;

namespace bindings {

    struct Message {
        PlayerID senderId;
        PlayerID recipientId;
        std::string content;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", "message"},
                {"data",
                 {{"senderId", senderId},
                  {"recipientId", recipientId},
                  {"content", content}}},
            };
        }

        static Message from_json(const nlohmann::json &j) {
            if (j.at("type") != "message") {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Message{data.at("senderId").get<PlayerID>(),
                           data.at("recipientId").get<PlayerID>(),
                           data.at("content").get<std::string>()};
        }
    };

} // namespace bindings

#endif // MESSAGE_HPP
