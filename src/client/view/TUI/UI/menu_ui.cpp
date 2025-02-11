/**
 * @file menu_ui.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Menu UI class definition file
 * @date 2025-02-10
 * 
 */

#include "menu_ui.hpp"
#include <ftxui/component/component.hpp>

MenuUi::MenuUi(std::shared_ptr<ScreenManager> screenManager, const std::string& title, std::vector<std::string> entries)
         : screenManager_(screenManager), title_(title), entries_(std::move(entries)), selected_(0) {}
   
void MenuUi::addSubMenu(const std::string& label, std::shared_ptr<MenuUi> submenu) {
    submenus_[label] = submenu;
}
   
void MenuUi::run() {
    using namespace ftxui;

    MenuOption option;
    option.on_enter = [this]() {
        std::string selected_entry = entries_[selected_];
        if (submenus_.count(selected_entry)) {
            submenus_[selected_entry]->run();
        } else {

        }
    };

    auto menu = Menu(&entries_, &selected_, option);
    screenManager_->loopScreen(menu);
}
