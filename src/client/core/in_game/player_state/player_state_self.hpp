#ifndef CLIENT_PLAYER_STATE_SELF_HPP
#define CLIENT_PLAYER_STATE_SELF_HPP

#include "../../../../common/types/types.hpp"
#include "../effects/timed_bonus.hpp"
#include "../effects/timed_penalty.hpp"
#include "abstract_player_state.hpp"

#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <queue>

enum class PenaltyType;

namespace client {

    /**
     * @brief Self player state. "Self" means that this packet contains all the
     * information about that player, it is supposed to be sent only to the
     * player themself.
     */
    struct PlayerStateSelf final : public AbstractPlayerState {
        std::optional<UserID> penaltyTarget;

        std::optional<Energy> energy;

        std::queue<PenaltyType> stashedPenalties;

        std::optional<client::TimedBonus> activeBonus;
        std::optional<client::TimedPenalty> activePenalty;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_SELF_HPP
