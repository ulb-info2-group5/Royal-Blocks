/**
 * @file main_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class header file
 * @date 2025-02-12
 * 
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "../UI/menu_ui.hpp"

class MainMenu : public MenuUi {
    public:
        /*
        * @brief Construct a new Main Menu object
        */
        MainMenu(ScreenManager *screenManager);

        /*
        * @brief Destroy the Main Menu object
        */
        ~MainMenu() = default;

        /*
        * @brief Run the main menu screen with all the components
        */
        
};

#endif // MAIN_MENU_HPP