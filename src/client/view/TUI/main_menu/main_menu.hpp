/**
 * @file main_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class declaration file
 * @date 2025-02-12
 * 
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>

/**
 * @brief Main menu of the game that will be displayed to the user
 * 
 */
class MainMenu {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

    public:
        /**
         * @brief Construct a new Main Menu object
         */
        MainMenu(std::shared_ptr<ftxui::ScreenInteractive>);

        /**
         * @brief Destroy the Main Menu object
         */
        ~MainMenu() = default;

        /**
         * @brief Render the main menu screen with all the components
         *
         */
        void render();
};

#endif // MAIN_MENU_HPP

