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
#include <vector>
#include <tuple>

enum class MainMenuState {
    PLAY,
    JOIN_GAME,
    SEND_MESSAGES,
    LOOK_RANKING,
    MANAGE_PROFILE,
    MANAGE_FRIENDS_LIST,
    EXIT,
    NONE,
};

/**
 * @brief Main menu of the game that will be displayed to the user
 * 
 */
class MainMenu {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

        /*
         * @brief Manage the profile of the user
         *
         * @param friendName The name of the friend to manage
         */
        void manageFriendlistScreen(const std::string &friendName);


    public:
        /*
         * @brief Construct a new Main Menu object
         */
        MainMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen);

        /*
         * @brief Destroy the Main Menu object
         */
        ~MainMenu() = default;

        /*
         * @brief Render the main menu screen with all the components by asking the screen manager to render the components
         *
         */
        MainMenuState render();

        /*
         * @brief Render the ranking of the players of the Endless mode
         *
         * @param ranking The ranking of the players of the Endless mode to display,
         * the vector has to be already sorted by the score of the players
         */
         void renderRanking(const std::vector<std::tuple<int, std::string, int>> &ranking);

        /*
        *@brief Launch and render the messagingMenu
        *
        */
        void renderMessagingMenu(const std::vector<std::string> &friendsList );

        /*
         * @brief Render the friends list of the user to display with all friends dislayed is a button
         *
         * @param friendsList The list of the friends of the user to display
         */
         void renderFriendsManager(const std::vector<std::string> &friendsList);
};

#endif // MAIN_MENU_HPP

