#ifndef CLIENT_TETRIS_EXTERNAL_HPP
#define CLIENT_TETRIS_EXTERNAL_HPP

#include "abstract_tetris.hpp"

namespace client {

    struct TetrisExternal : public AbstractTetris {
        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_TETRIS_EXTERNAL_HPP
