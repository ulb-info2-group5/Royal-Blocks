#ifndef BINDINGS_GAME_OVER_HPP
#define BINDINGS_GAME_OVER_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {
    struct GameOver{
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::GameOver},
            };
        }
        static GameOver from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::GameOver) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return GameOver{};
        }
    };
} 

#endif //BINDINGS_GAME_OVER_HPP
