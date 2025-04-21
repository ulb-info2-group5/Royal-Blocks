#ifndef BINDINGS_QUIT_GAME_HPP
#define BINDINGS_QUIT_GAME_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to quit the current game.
     */
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
