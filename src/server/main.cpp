#include "tetris_main_server/tetris_main_server.hpp"

int main(int argc, char *argv[]) {
    TetrisMainServer tetrisMainServer(argc, argv);
    tetrisMainServer.run();
    return 0;
}