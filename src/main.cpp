#include "tetris/event.hpp"
#include "tetris/tetris.hpp"
#include <cstdio>
#include <pthread.h>

void *inputHandlerRoutine(void *arg) {
    Tetris *tetris = static_cast<Tetris *>(arg);
    char key;

    // TODO: add thread-safety for this
    while (tetris->getIsAlive()) {
        key = getchar();

        switch (key) {
        case '\n': // TODO: remove this when switching to ncurses
            break;
        case 'h':
            tetris->addQueueEvent(EventType::MoveLeft);
            break;
        case 'l':
            tetris->addQueueEvent(EventType::MoveRight);
            break;
        default:
            std::cout << "neither h nor l" << std::endl;
            break;
        }
    }

    return nullptr;
}

int main() {
    Tetris tetris;

    std::cout << tetris.getIsAlive() << std::endl;

    pthread_t inputHandler;
    pthread_create(&inputHandler, nullptr, inputHandlerRoutine,
                   static_cast<void *>(&tetris));

    tetris.run();

    pthread_join(inputHandler, nullptr);

    return 0;
}
