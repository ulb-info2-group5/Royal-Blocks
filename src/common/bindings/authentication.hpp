#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

using PlayerID = size_t;

namespace bindings {

    struct Authentication {
        std::string nickname;
        std::string password;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::Authentication},
                                  {"data",
                                   {
                                       {"nickname", nickname},
                                       {"password", password},
                                   }}};
        }

        static Authentication from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Authentication) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Authentication{data.at("nickname").get<std::string>(),
                                  data.at("password").get<std::string>()};
        }
    };

} // namespace bindings

#endif // AUTHENTICATION_HPP
