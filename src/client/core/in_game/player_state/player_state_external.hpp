#ifndef CLIENT_PLAYER_STATE_EXTERNAL_HPP
#define CLIENT_PLAYER_STATE_EXTERNAL_HPP

#include <nlohmann/json.hpp>

#include "../../../../common/types/types.hpp"
#include "abstract_player_state.hpp"

namespace client {

    /**
     * @brief External player state. "External" means that some data is hidden
     * because only that player can see it.
     */
    struct PlayerStateExternal final : public AbstractPlayerState {
        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_EXTERNAL_HPP
