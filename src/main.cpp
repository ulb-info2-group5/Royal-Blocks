#include "../include/grid/print_grid.hpp"
#include "tetris/event_type.hpp"
#include "tetris/tetris.hpp"
#include <chrono>
#include <cstdio>
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
        key = getchar();

        switch (key) {
        case 'h': // left
            tetris->addEvent(EventType::MoveLeft);
            break;
        case 'l': // right
            tetris->addEvent(EventType::MoveRight);
            break;
        case 'j': // down
            tetris->addEvent(EventType::MoveDown);
            break;
        case 'G': // big drop
            tetris->addEvent(EventType::BigDrop);
            break;
        case 'g': // rotate clockwise
            tetris->addEvent(EventType::RotateClockwise);
            break;
        case 'f': // rotate counter-clockwise
            tetris->addEvent(EventType::RotateCounterClockwise);
            break;
        case ' ': // rotate counter-clockwise
            tetris->addEvent(EventType::RotateClockwise);
            break;
        case 'q':
            tetris->addEvent(EventType::Quit);
        case 0x1b:     // special case like arrows
            getchar(); // '['
            key = getchar();
            switch (key) {

            case 'A': // up
                tetris->addEvent(EventType::BigDrop);
                break;
            case 'B': // down
                tetris->addEvent(EventType::MoveDown);
                break;
            case 'C': // right
                tetris->addEvent(EventType::MoveRight);
                break;
            case 'D': // left
                tetris->addEvent(EventType::MoveLeft);
                break;

            default:
                break;

                break;
            }
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

    ncurses_init();
    fflush(stdout);

    tetris.run();

    pthread_join(inputHandler, nullptr);
    pthread_join(clockHandler, nullptr);

    return 0;
}
