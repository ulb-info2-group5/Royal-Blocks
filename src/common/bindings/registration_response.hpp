#ifndef BINDINGS_REGISTRATION_RESPONSE_HPP
#define BINDINGS_REGISTRATION_RESPONSE_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Represents the response to a registration request.
     *
     * This binding is used to indicate whether a registration attempt was
     * successful.
     */
    struct RegistrationResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::RegistrationResponse},
                {"data",
                 {
                     {"success", success},
                 }}};
        }

        static RegistrationResponse from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::RegistrationResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return RegistrationResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_REGISTRATION_RESPONSE_HPP
