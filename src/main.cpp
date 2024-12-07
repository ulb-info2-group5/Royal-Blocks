#include "tetris/event.hpp"
#include "tetris/tetris.hpp"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <thread>

void *clockRoutine(void *arg) {
    Tetris *tetris = static_cast<Tetris *>(arg);

    float frequency = 2;
    std::chrono::duration period = std::chrono::seconds(1) / frequency;

    while (tetris->getIsAlive()) {
        std::chrono::time_point start = std::chrono::steady_clock::now();

        tetris->addQueueEvent(EventType::MoveDown);

        std::chrono::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration delta =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (delta < period) {
            std::this_thread::sleep_for(period - delta);
        }
    }

    return 0;
}

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

    pthread_t inputHandler, clockHandler;
    pthread_create(&inputHandler, nullptr, inputHandlerRoutine,
                   static_cast<void *>(&tetris));
    pthread_create(&clockHandler, nullptr, clockRoutine,
                   static_cast<void *>(&tetris));

    tetris.run();

    pthread_join(inputHandler, nullptr);
    pthread_join(clockHandler, nullptr);

    return 0;
}
