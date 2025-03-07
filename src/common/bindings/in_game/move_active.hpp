#ifndef BINDINGS_MOVE_ACTIVE_HPP
#define BINDINGS_MOVE_ACTIVE_HPP

#include "../../tetris_lib/tetromino/tetromino.hpp"

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct MoveActive {
        TetrominoMove tetrominoMove;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::MoveActive},
                                  {"data",
                                   {
                                       {"tetrominoMove", tetrominoMove},
                                   }}};
        }

        static MoveActive from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::MoveActive) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return MoveActive{data.at("tetrominoMove").get<TetrominoMove>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_MOVE_ACTIVE_HPP
