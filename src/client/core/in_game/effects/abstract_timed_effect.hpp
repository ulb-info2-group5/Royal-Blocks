#ifndef CLIENT_ABSTRACT_TIMED_EFFECT_HPP
#define CLIENT_ABSTRACT_TIMED_EFFECT_HPP

#include <nlohmann/json.hpp>

namespace client {

    /**
     * @brief Abtract class for all timed-effects.
     */
    struct AbstractTimedEffect {
        double elapsedTime;

        virtual ~AbstractTimedEffect() = default;

        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_TIMED_EFFECT_HPP
