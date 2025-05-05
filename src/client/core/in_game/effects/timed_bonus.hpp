#ifndef TIMED_BONUS_HPP
#define TIMED_BONUS_HPP

#include "abstract_timed_effect.hpp"
#include "nlohmann/json_fwd.hpp"

enum class BonusType;

namespace client {

    /**
     * @brief Timed bonus class.
     */
    struct TimedBonus final : public client::AbstractTimedEffect {
        BonusType bonusType;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // TIMED_BONUS_HPP
