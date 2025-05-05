#ifndef TIMED_PENALTY_HPP
#define TIMED_PENALTY_HPP

#include "abstract_timed_effect.hpp"

#include <nlohmann/json_fwd.hpp>
enum class PenaltyType;


namespace client {

    /**
     * @brief Timed penalty class.
     */
    struct TimedPenalty final : public client::AbstractTimedEffect {
        PenaltyType penaltyType;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // TIMED_PENALTY_HPP
