#ifndef CLIENT_PLAYER_STATE_EXTERNAL_HPP
#define CLIENT_PLAYER_STATE_EXTERNAL_HPP

#include <nlohmann/json.hpp>

#include "../../../../common/types/types.hpp"
#include "abstract_player_state.hpp"

namespace client {

    struct PlayerStateExternal final : public AbstractPlayerState {
        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_EXTERNAL_HPP
