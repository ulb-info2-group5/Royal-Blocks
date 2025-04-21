#ifndef BINDINGS_REGISTRATION_HPP
#define BINDINGS_REGISTRATION_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent to the server when a client attempts to
     * register.
     */
    struct Registration {
        std::string nickname;
        std::string password;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::Registration},
                                  {"data",
                                   {
                                       {"nickname", nickname},
                                       {"password", password},
                                   }}};
        }

        static Registration from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Registration) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Registration{data.at("nickname").get<std::string>(),
                                data.at("password").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_REGISTRATION_HPP
