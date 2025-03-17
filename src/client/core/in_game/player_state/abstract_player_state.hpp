#ifndef CLIENT_ABSTRACT_PLAYER_STATE_HPP
#define CLIENT_ABSTRACT_PLAYER_STATE_HPP

#include <nlohmann/json.hpp>

#include "../../../../common/types/types.hpp"

namespace client {

    struct AbstractPlayerState {
        UserID userID;
        Score score;
        bool isAlive;
        std::string username;

        virtual ~AbstractPlayerState() = default;

        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_PLAYER_STATE_HPP
