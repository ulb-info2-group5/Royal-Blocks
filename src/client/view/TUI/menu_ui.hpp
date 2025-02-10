/**
 * @file menu_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Menu UI class declaration file
 * @date 2025-02-10
 * 
 */

#ifndef MENU_UI_HPP
#define MENU_UI_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "screen_manager.hpp"

class MenuUi {
    protected:
        std::shared_ptr<ScreenManager> screenManager_;
        std::string title_;
        std::vector<std::string> entries_;
        int selected_;
        std::unordered_map<std::string, std::shared_ptr<MenuUi>> submenus_;

    public:
        MenuUi(std::shared_ptr<ScreenManager> screenManager, const std::string& title, std::vector<std::string> entries);

        void AddSubMenu(const std::string& label, std::shared_ptr<MenuUi> submenu);

        virtual void run();
   
};

#endif // MENU_UI_HPP