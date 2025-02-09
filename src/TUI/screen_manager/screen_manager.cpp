/**
* @file screen_manager.cpp
* @author Ethan Van Ruyskensvelde
* @brief ScreenManager class implementation file
* @date 2025-02-09
*
*/

#include "screen_manager.hpp"


ScreenManager::ScreenManager() : screen_(ftxui::ScreenInteractive::TerminalOutput()) {}

void ScreenManager::SetComponent(ftxui::Component component) {
    mainComponent_ = component;
}
void ScreenManager::Run() {
    screen_.Loop(mainComponent_);
}
void ScreenManager::Exit() {
    screen_.Exit();
}