#ifndef TIMED_PENALTY_HPP
#define TIMED_PENALTY_HPP

#include "../../../../common/tetris_royal_lib/effect/penalty/penalty_type.hpp"
#include "abstract_timed_effect.hpp"

#include <nlohmann/json.hpp>

namespace client {

    struct TimedPenalty : public client::AbstractTimedEffect {
        PenaltyType penaltyType;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // TIMED_PENALTY_HPP
