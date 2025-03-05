#ifndef HOLD_NEXT_TETROMINO_HPP
#define HOLD_NEXT_TETROMINO_HPP

#include "../bindings.hpp"

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

#endif // HOLD_NEXT_TETROMINO_HPP
