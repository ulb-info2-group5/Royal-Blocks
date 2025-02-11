#include "screen_manager.hpp"

ScreenManager::ScreenManager() : screen_(ftxui::ScreenInteractive::Fullscreen()) {}

void ScreenManager::loopScreen(const ftxui::Component component) {
    screen_.Loop(component);
}

void ScreenManager::ExitLoopClosure() {
    screen_.ExitLoopClosure()();
}