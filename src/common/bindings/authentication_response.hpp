#ifndef BINDINGS_AUTHENTICATION_RESPONSE_HPP
#define BINDINGS_AUTHENTICATION_RESPONSE_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct AuthenticationResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::AuthenticationResponse},
                                  {"data",
                                   {
                                       {"success", success},
                                   }}};
        }

        static AuthenticationResponse from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::AuthenticationResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return AuthenticationResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_AUTHENTICATION_RESPONSE_HPP
