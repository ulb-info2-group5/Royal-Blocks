#ifndef BINDINGS_CHANGE_USERNAME_HPP
#define BINDINGS_CHANGE_USERNAME_HPP

#include "binding_type.hpp"
#include <string>

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Bindings sent by the client to change their username.
     */
    struct ChangeUsername {
        std::string username;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::ChangeUsername},
                                  {"data",
                                   {
                                       {"username", username},
                                   }}};
        }

        static ChangeUsername from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::ChangeUsername) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return ChangeUsername{data.at("username").get<std::string>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_CHANGE_USERNAME_HPP
