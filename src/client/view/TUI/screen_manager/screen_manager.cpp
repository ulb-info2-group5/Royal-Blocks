#include "screen_manager.hpp"
#include <csignal>
#include <ftxui/component/component_base.hpp>


ScreenManager::ScreenManager() : screen_(ftxui::ScreenInteractive::Fullscreen()) {}

ScreenManager::~ScreenManager() {
    screen_.Exit();
}

void ScreenManager::loopScreen(const ftxui::Component &component) {
    screen_.Loop(component);
}

void ScreenManager::exitLoop() {
    screen_.ExitLoopClosure()();
}

void ScreenManager::exit() {
    screen_.Exit();
}