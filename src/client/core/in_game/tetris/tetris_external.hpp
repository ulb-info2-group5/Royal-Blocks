#ifndef CLIENT_TETRIS_EXTERNAL_HPP
#define CLIENT_TETRIS_EXTERNAL_HPP

#include "abstract_tetris.hpp"

#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief External tetris. "External" means that some data is hidden
     * because only that player can see it.
     */
    struct TetrisExternal final : public AbstractTetris {
        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_TETRIS_EXTERNAL_HPP
