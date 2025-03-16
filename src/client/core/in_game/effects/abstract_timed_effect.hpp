#ifndef CLIENT_ABSTRACT_TIMED_EFFECT_HPP
#define CLIENT_ABSTRACT_TIMED_EFFECT_HPP

#include <nlohmann/json.hpp>

namespace client {

    struct AbstractTimedEffect {
        double elapsedTime;

        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_TIMED_EFFECT_HPP
