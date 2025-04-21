#ifndef BINDINGS_CHANGE_USERNAME_RESPONSE_HPP
#define BINDINGS_CHANGE_USERNAME_RESPONSE_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    /**
     * @brief Binding sent by the server to a client as a response to a password
     * change. Indicates succes or fail.
     */
    struct ChangeUsernameResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::ChangeUsernameResponse},
                                  {"data",
                                   {
                                       {"success", success},
                                   }}};
        }

        static ChangeUsernameResponse from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::ChangeUsernameResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return ChangeUsernameResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_CHANGE_USERNAME_RESPONSE
