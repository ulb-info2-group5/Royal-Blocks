#ifndef BINDINGS_MESSAGE_HPP
#define BINDINGS_MESSAGE_HPP

#include "binding_type.hpp"

#include "../../common/types/types.hpp"

#include <nlohmann/json.hpp>
#include <string>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding representing a message.
     */
    struct Message {
        UserID recipientId;
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
            return Message{data.at("recipientId").get<UserID>(),
                           data.at("content").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_MESSAGE_HPP
