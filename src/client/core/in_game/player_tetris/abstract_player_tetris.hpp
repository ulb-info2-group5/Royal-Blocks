#ifndef CLIENT_ABSTRACT_PLAYER_TETRIS_HPP
#define CLIENT_ABSTRACT_PLAYER_TETRIS_HPP

#include <nlohmann/json.hpp>

namespace client {

    struct AbstractPlayerTetris {
        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_PLAYER_TETRIS_HPP
