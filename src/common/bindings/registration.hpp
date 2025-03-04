#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <nlohmann/json.hpp>
#include <string>

using PlayerID = size_t;

namespace bindings {

    struct Registration {
        std::string nickname;
        std::string password;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", "registration"},
                {"data",
                 {
                     {"nickname", nickname},
                     {"password", password},
                 }},
            };
        }

        static Registration from_json(const nlohmann::json &j) {
            if (j.at("type") != "registration") {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Registration{data.at("nickname").get<std::string>(),
                                data.at("password").get<std::string>()};
        }
    };

} // namespace bindings

#endif // REGISTRATION_HPP
