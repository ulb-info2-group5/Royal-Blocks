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
#include <vector>
#include <tuple>

#include "../screen_manager.hpp"

/**
 * @brief Main menu of the game that will be displayed to the user
 * 
 */
class MainMenu {
    private:
        ScreenManager *screenManager_;

        /*
         * @brief Render the ranking of the players of the Endless mode
         *
         * @param ranking The ranking of the players of the Endless mode to display,
         * the vector has to be already sorted by the score of the players
         */
        void renderRanking(const std::vector<std::tuple<int, std::string, int>> &ranking);

        /*
         * @brief Render the friends list of the user to display with all friends dislayed is a button
         *
         * @param friendsList The list of the friends of the user to display
         */
        void renderFriendsList(const std::vector<std::string> &friendsList);

        /*
         * @brief Manage the profile of the user
         *
         * @param friendName The name of the friend to manage
         */
        void manageFriendlistScren(const std::string &friendName);

        /*
        *@brief Launch and render the messagingMenu
        *
        */
        void renderMessagingMenu(const std::vector<std::string> &friendsList );


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
         * @brief Render the main menu screen with all the components by asking the screen manager to render the components
         *
         */
        void render();
};

#endif // MAIN_MENU_HPP

