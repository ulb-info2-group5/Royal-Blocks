#ifndef BINDINGS_CREATE_GAME_HPP
#define BINDINGS_CREATE_GAME_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to create a new game.
     */
    struct CreateGame {
        GameMode gameMode;
        size_t targetNumPlayers;

        nlohmann::json to_json() const {
            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::CreateGame},
                                  {"data",
                                   {
                                       {"gameMode", gameMode},
                                       {"targetNumPlayers", targetNumPlayers},
                                   }}};
        }

        static CreateGame from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::CreateGame) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return CreateGame{data.at("gameMode").get<GameMode>(),
                              data.at("targetNumPlayers").get<size_t>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_CREATE_GAME_HPP
