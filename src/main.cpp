#include "tetris/event_type.hpp"
#include "tetris/tetris.hpp"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <thread>

void *clockRoutine(void *arg) {
    Tetris *tetris = static_cast<Tetris *>(arg);

    constexpr float frequency = 1;
    constexpr std::chrono::duration period =
        std::chrono::seconds(1) / frequency;

    while (tetris->getIsAlive()) {
        std::chrono::time_point start = std::chrono::steady_clock::now();

        tetris->addEvent(EventType::ClockTick);

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

    while (tetris->getIsAlive()) {
        // This makes the routine take one more character even
        // when the game is finshed, will be solved when using
        // ncurses
        key = getchar();

        switch (key) {
        case '\n': // TODO: remove this when switching to ncurses
            break;
        case 'h': // left
            tetris->addEvent(EventType::MoveLeft);
            break;
        case 'l': // right
            tetris->addEvent(EventType::MoveRight);
            break;
        case 'j': // down
            tetris->addEvent(EventType::MoveDown);
            break;
        case 'J': // big drop
            tetris->addEvent(EventType::BigDrop);
            break;
        case 'g': // rotate clockwise
            tetris->addEvent(EventType::RotateClockwise);
            break;
        case 'f': // rotate counter-clockwise
            tetris->addEvent(EventType::RotateCounterClockwise);
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
