#ifndef BINDINGS_JOIN_FRIEND_HPP
#define BINDINGS_JOIN_FRIEND_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "in_game/select_target.hpp"

#include <nlohmann/json.hpp>
#include <optional>

namespace bindings {

    struct JoinGame {
        GameMode gameMode;
        std::optional<PlayerID> friendId;

        nlohmann::json to_json() const {
            nlohmann::json j_data;

            j_data["gameMode"] = gameMode;

            if (friendId) {
                j_data["friendId"] = friendId.value();
            } else {
                j_data["friendId"] = nullptr;
            }

            return nlohmann::json{{"type", BindingType::JoinGame},
                                  {"data", j_data}};
        }

        static JoinGame from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::JoinGame) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");

            return JoinGame{
                data.at("gameMode").get<GameMode>(),

                data.at("friendId").is_null()
                    ? std::nullopt
                    : std::make_optional(data.at("friendId").get<PlayerID>())};
        }
    };

} // namespace bindings

#endif // BINDINGS_JOIN_FRIEND_HPP
