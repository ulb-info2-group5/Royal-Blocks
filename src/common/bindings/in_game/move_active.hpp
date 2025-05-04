#ifndef BINDINGS_MOVE_ACTIVE_HPP
#define BINDINGS_MOVE_ACTIVE_HPP

#include "../../tetris_lib/tetromino/abstract_tetromino.hpp"

#include "../binding_type.hpp"
#include "../constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to move the active tetromino in a
     * certain direction.
     */
    struct MoveActive {
        TetrominoMove tetrominoMove;

        nlohmann::json to_json() const {
            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::MoveActive},
                                  {"data",
                                   {
                                       {"tetrominoMove", tetrominoMove},
                                   }}};
        }

        static MoveActive from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::MoveActive) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return MoveActive{data.at("tetrominoMove").get<TetrominoMove>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_MOVE_ACTIVE_HPP
