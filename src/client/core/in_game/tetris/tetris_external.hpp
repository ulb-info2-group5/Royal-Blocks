#ifndef CLIENT_TETRIS_EXTERNAL_HPP
#define CLIENT_TETRIS_EXTERNAL_HPP

#include "../../../../common/tetris_lib/board/board.hpp"

namespace client {

    struct TetrisExternal {
        Board board;

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETRIS_EXTERNAL_HPP
