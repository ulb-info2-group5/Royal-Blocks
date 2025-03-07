#ifndef BINDINGS_QUIT_GAME_HPP
#define BINDINGS_QUIT_GAME_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct QuitGame {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::QuitGame},
            };
        }

        static QuitGame from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::QuitGame) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return QuitGame{};
        }
    };

} // namespace bindings

#endif // BINDINGS_QUIT_GAME_HPP
