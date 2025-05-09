#ifndef BINDINGS_CHANGE_PASSWORD_HPP
#define BINDINGS_CHANGE_PASSWORD_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>
#include <string>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Bindings sent by the client to change their password.
     */
    struct ChangePassword {
        std::string password;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::ChangePassword},
                {"data",
                 {
                     {"password", password},
                 }}};
        }

        static ChangePassword from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::ChangePassword) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return ChangePassword{data.at("password").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_CHANGE_PASSWORD_HPP
