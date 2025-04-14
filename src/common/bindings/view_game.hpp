#ifndef BINDINGS_VIEW_GAME_HPP
#define BINDINGS_VIEW_GAME_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "../tetris_royal_lib/player_state/player_state.hpp"
#include "in_game/select_target.hpp"

#include <nlohmann/json.hpp>
#include <optional>

<<<<<<< HEAD
/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the player to spectate/view another user's game.
     */
    struct ViewGame {
        UserID targetUser; // the user to spectate
=======
namespace bindings {

    struct ViewGame{
        UserID targetUser;
>>>>>>> 7f185a13 (add bindings viewGame)
        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::ViewGame},
                                  {"data",
                                   {
                                       {"targetUser", targetUser},
                                   }}};
        }

        static ViewGame from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::ViewGame) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return ViewGame{
                data.at("targetUser").get<UserID>(),
            };
        }
<<<<<<< HEAD
    };
=======
    
    };
        
>>>>>>> 7f185a13 (add bindings viewGame)

} // namespace bindings

#endif // BINDINGS_VIEW_GAME_HPP
