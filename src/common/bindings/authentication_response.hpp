#ifndef AUTHENTICATION_RESPONSE_HPP
#define AUTHENTICATION_RESPONSE_HPP

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct AuthenticationResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", "authenticationResponse"},
                {"data", {{"success", success}}},
            };
        }

        static AuthenticationResponse from_json(const nlohmann::json &j) {
            if (j.at("type") != "authenticationResponse") {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return AuthenticationResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // AUTHENTICATION_RESPONSE_HPP
