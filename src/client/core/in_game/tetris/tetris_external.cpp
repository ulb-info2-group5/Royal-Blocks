#include "tetris_external.hpp"

#include <map>
#include <nlohmann/json.hpp>

#include "board/board.hpp"

void client::TetrisExternal::deserialize(const nlohmann::json &j) {
    board.deserialize(j.at("board"));
}
