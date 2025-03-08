#ifndef CLIENT_PLAYER_STATE_EXTERNAL_HPP
#define CLIENT_PLAYER_STATE_EXTERNAL_HPP

#include <nlohmann/json.hpp>

#include <cstddef>

using PlayerID = size_t;
using Score = size_t;
using Energy = size_t;

namespace client {

    struct PlayerStateExternal {
        PlayerID playerID_;
        Score score_;
        bool isAlive_;

        /* ------------------------------------------------
         *          Serialization
         * ------------------------------------------------*/

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_EXTERNAL_HPP
