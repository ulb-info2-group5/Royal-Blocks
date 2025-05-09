#ifndef BINDINGS_AUTHENTICATION_RESPONSE_HPP
#define BINDINGS_AUTHENTICATION_RESPONSE_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Represents the response to an authentication request.
     *
     * This binding is used to indicate whether an authentication attempt was
     * successful.
     */
    struct AuthenticationResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::AuthenticationResponse},
                {"data",
                 {
                     {"success", success},
                 }}};
        }

        static AuthenticationResponse from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD)
                != BindingType::AuthenticationResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return AuthenticationResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_AUTHENTICATION_RESPONSE_HPP
