/**
* @file screen_manager.cpp
* @author Ethan Van Ruyskensvelde
* @brief ScreenManager class header file
* @date 2025-02-09
*
*/

#include "screen_manager.hpp"


ScreenManager::ScreenManager() : screen(ftxui::ScreenInteractive::TerminalOutput()) {}

void ScreenManager::SetComponent(ftxui::Component component) {
    mainComponent = component;
}
void ScreenManager::Run() {
    screen.Loop(mainComponent);
}
void ScreenManager::Exit() {
    screen.Exit();
}