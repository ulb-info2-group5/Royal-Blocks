#ifndef CLIENT_ABSTRACT_TETRIS_HPP
#define CLIENT_ABSTRACT_TETRIS_HPP

#include "../../../../common/tetris_lib/board/board.hpp"

namespace client {

    struct AbstractTetris {
        Board board;

        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_TETRIS_HPP
