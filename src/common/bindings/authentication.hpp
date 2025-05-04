#ifndef BINDINGS_AUTHENTICATION_HPP
#define BINDINGS_AUTHENTICATION_HPP

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
     * @brief Binding sent to the server when a client attempts to
     * authentify.
     */
    struct Authentication {
        std::string nickname;
        std::string password;

        nlohmann::json to_json() const {
            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::Authentication},
                                  {"data",
                                   {
                                       {"nickname", nickname},
                                       {"password", password},
                                   }}};
        }

        static Authentication from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::Authentication) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Authentication{data.at("nickname").get<std::string>(),
                                  data.at("password").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_AUTHENTICATION_HPP
