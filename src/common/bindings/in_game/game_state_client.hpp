#ifndef GAME_STATE_CLIENT_HPP
#define GAME_STATE_CLIENT_HPP

#include "../../../client/core/in_game/game_state/game_state.hpp"

#include "../../../client/core/in_game/game_state/game_state_viewer.hpp"

#include "../binding_type.hpp"

#include <memory>
#include <nlohmann/json.hpp>

namespace bindings {

    namespace GameStateMessage {

        /**
         * @brief Deserializes the given GameState binding into a
         * client::GameState.
         */
        client::GameState deserializeForPlayer(const nlohmann::json &j) {
            if (j.at("type") != BindingType::GameState) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            client::GameState gameStateBinding;
            gameStateBinding.deserialize(data.at("gameState"));
            return gameStateBinding;
        };

        client::GameStateViewer deserializeForViewer(const nlohmann::json &j) {
            if (j.at("type") != BindingType::GameStateViewer) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            client::GameStateViewer gameStateViewerBinding;
            gameStateViewerBinding.deserialize(data.at("gameState"));

            return gameStateViewerBinding;
        };

        std::unique_ptr<client::AbstractGameState>
        deserialize(const nlohmann::json &j) {
            std::unique_ptr<client::AbstractGameState> ret;

            if (j.at("type") == BindingType::GameStateViewer) {
                ret = std::make_unique<client::GameStateViewer>(
                    GameStateMessage::deserializeForViewer(j));

                return ret;
            } else if (j.at("type") == BindingType::GameState) {
                ret = std::make_unique<client::GameState>(
                    GameStateMessage::deserializeForPlayer(j));

                return ret;
            } else {
                throw std::runtime_error("Invalid type field in JSON");
            }
        }

    } // namespace GameStateMessage

} // namespace bindings

#endif // BINDING_GAME_STATE_CLIENT_HPP
