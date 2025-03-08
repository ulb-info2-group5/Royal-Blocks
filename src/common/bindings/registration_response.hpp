#ifndef BINDINGS_REGISTRATION_RESPONSE_HPP
#define BINDINGS_REGISTRATION_RESPONSE_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct RegistrationResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::RegistrationResponse},
                                  {"data",
                                   {
                                       {"success", success},
                                   }}};
        }

        static RegistrationResponse from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::RegistrationResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return RegistrationResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_REGISTRATION_RESPONSE_HPP
