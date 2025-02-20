#include "player_tetris.hpp"
#include "tetris/tetris.hpp"

nlohmann::json PlayerTetris::serializeSelf() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serializeSelf();
    j["tetris"] = tetris_.serializeSelf();

    return j;
}

nlohmann::json PlayerTetris::serializeExternal() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serializeExternal();
    j["tetris"] = tetris_.serializeExternal();

    return j;
}
