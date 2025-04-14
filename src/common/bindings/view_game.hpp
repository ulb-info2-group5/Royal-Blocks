#ifndef BINDINGS_VIEW_GAME_HPP
#define BINDINGS_VIEW_GAME_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "../tetris_royal_lib/player_state/player_state.hpp"
#include "in_game/select_target.hpp"

#include <nlohmann/json.hpp>
#include <optional>

namespace bindings {

    struct ViewGame{
        UserID targetUser;
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
    
    };
        

} // namespace bindings

#endif // BINDINGS_VIEW_GAME_HPP
