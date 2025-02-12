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

#include "../screen_manager/screen_manager.hpp"

class MenuUi {
    protected:
        ScreenManager * screenManager_;
        std::string title_;
        std::vector<std::string> entries_;
        int selected_;
        std::unordered_map<std::string, std::shared_ptr<MenuUi>> submenus_;

    public:
        /*
        * @brief Construct a new Menu Ui object
        */
        MenuUi(ScreenManager *screenManager, const std::string& title, std::vector<std::string> entries);

        /*
        * @brief Destroy the Menu Ui object
        */
       virtual  ~MenuUi() = default;

        /*
        * @brief Add a submenu (a MenuUi) to the menu with a label
        *
        * @param label the label of the submenu
        * @param submenu the submenu to add
        */
        void addSubMenu(const std::string& label, std::shared_ptr<MenuUi> submenu);

        /*
        * @brief Run the menu screen with all the components
        */
        virtual void run();
   
};

#endif // MENU_UI_HPP