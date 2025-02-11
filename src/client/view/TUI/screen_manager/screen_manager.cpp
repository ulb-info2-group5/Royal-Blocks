#include "screen_manager.hpp"
#include <csignal>

/*
* Handle the signal SIGINT (Ctrl+C) to exit the program
*/
void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::exit(0);
    }
}

ScreenManager::ScreenManager() : screen_(ftxui::ScreenInteractive::Fullscreen()) {
    std::signal(SIGINT, handleSignal);

}

void ScreenManager::loopScreen(const ftxui::Component component) {
    screen_.Loop(component);
}

void ScreenManager::ExitLoopClosure() {
    screen_.ExitLoopClosure()();
}