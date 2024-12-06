#include "tetris/event.hpp"
#include "tetris/tetris.hpp"
#include <cstdio>
#include <pthread.h>

void *inputHandlerRoutine(void *arg) {
    Tetris *tetris = static_cast<Tetris *>(arg);

    char key;

    while (true) {
        key = getchar();

        switch (key) {
        case 'h':
            tetris->addQueueEvent(EventType::moveLeft);
            break;
        case 'l':
            tetris->addQueueEvent(EventType::moveRight);
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

    pthread_t inputHandler;
    pthread_create(&inputHandler, nullptr, inputHandlerRoutine,
                   static_cast<void *>(&tetris));

    tetris.run();

    return 0;
}
