#ifndef CLIENT_PLAYER_STATE_EXTERNAL_HPP
#define CLIENT_PLAYER_STATE_EXTERNAL_HPP

#include <nlohmann/json.hpp>

#include "../../../../common/types/types.hpp"

namespace client {

    struct PlayerStateExternal {
        UserID userID;
        Score score;
        bool isAlive;
        std::string username;

        /* ------------------------------------------------
         *          Serialization
         * ------------------------------------------------*/

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_EXTERNAL_HPP
