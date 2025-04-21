#ifndef BINDINGS_HOLD_ACTIVE_TETROMINO_HPP
#define BINDINGS_HOLD_ACTIVE_TETROMINO_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct HoldActiveTetromino {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::HoldActiveTetromino},
            };
        }

        static HoldActiveTetromino from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::HoldActiveTetromino) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return HoldActiveTetromino{};
        }
    };

} // namespace bindings

#endif // BINDINGS_HOLD_ACTIVE_TETROMINO_HPP
