#ifndef BINDINGS_HOLD_NEXT_TETROMINO_HPP
#define BINDINGS_HOLD_NEXT_TETROMINO_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct HoldNextTetromino {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::HoldNextTetromino},
            };
        }

        static HoldNextTetromino from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::HoldNextTetromino) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return HoldNextTetromino{};
        }
    };

} // namespace bindings

#endif // BINDINGS_HOLD_NEXT_TETROMINO_HPP
