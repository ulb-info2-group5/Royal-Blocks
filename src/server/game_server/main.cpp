#include "game_mode/game_mode.hpp"
#include "game_server.hpp"
#include "tetromino/tetromino.hpp"

int main() {
    GameServer gameServer{GameMode::Dual, {0, 1}};

    for (int i = 0; i < 200; i++) {
        gameServer.enqueueBinding(0, bindings::BigDrop{}.to_json().dump());
    }

    // -----------------------------
    // gameServer.enqueueBinding(1, bindings::BigDrop{}.to_json().dump());
    //
    // gameServer.enqueueBinding(1,
    // bindings::SelectTarget{2}.to_json().dump());
    //
    // gameServer.enqueueBinding(
    //     1, bindings::MoveActive{TetrominoMove::Right}.to_json().dump());
    // -----------------------------

    gameServer.run();
}
