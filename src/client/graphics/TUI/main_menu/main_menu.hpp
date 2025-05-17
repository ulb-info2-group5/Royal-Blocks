/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TUI_MAIN_MENU_HPP
#define TUI_MAIN_MENU_HPP

#include "../friends_menu/friends_menu.hpp"
#include "../game_menu/game_menu.hpp"
#include "../messaging/messaging.hpp"

#include <ftxui/component/component.hpp>
#include <string>

class Controller;

namespace TUI {

    class MainTUI;

    /**
     * @brief Main menu of the game that will be displayed to the user
     *
     */
    class MainMenu final {
      public:
        enum class MainMenuState {
            CREATE_GAME,
            JOIN_GAME,
            SEND_MESSAGES_TO_FRIENDS,
            LOOK_RANKING,
            MANAGE_PROFILE,
            MANAGE_FRIENDS_LIST,
            EXIT,
            BACK,
            NONE,
        };

      private:
        /*
         * @brief The screen to use to render the components
         */
        MainTui &mainTui_;

        /*
         * @brief The controller to ask for the data to show to the user
         */
        Controller &controller_;

        MainMenuState state_;

        /*
         * @brief The classes needed to display the different menus (friends,
         * messages, game)
         */
        FriendsMenu friendsMenu_;
        Messaging messagingMenu_;
        GameMenu gameMenu_;

        ftxui::Component buttonPlay_;
        ftxui::Component buttonJoinGame_;
        ftxui::Component buttonSendMessagesToFriends_;
        ftxui::Component buttonLookRanking_;
        ftxui::Component buttonManageProfile_;
        ftxui::Component buttonManageFriendsList_;
        ftxui::Component buttonExit_;

        ftxui::Component buttonBack_;
        ftxui::Component buttonOK_;

        ftxui::Elements rowsRanking_;

        ftxui::Components friendButtons_;
        ftxui::Component buttonAddFriend_;
        ftxui::Component friendsContainer_;

        ftxui::Component inputChangeUsername_;
        ftxui::Component inputChangePassword_;
        ftxui::Component submitButton_;
        std::string username_;
        std::string password_;

        ftxui::Component mainMenuWindow_;
        ftxui::Component rankingWindow_;
        ftxui::Component friendManagerWindow_;
        ftxui::Component profileManagerWindow_;

        /*
         * @brief Handle the choice of the user in the main menu
         */
        void handleChoice();

        /*
         * @brief Create the main menu buttons (play, join game, send messages
         * to friends, look ranking, manage profile, manage friends list, exit)
         */
        void createMainMenuButtons();

        /*
         * @brief Display the main window of the main menu
         */
        void displayMainWindow();

        /*
         * @brief Display the ranking window of the Endless mode
         */
        void displayRankingWindow();

        /*
         * @brief Display the buttons of the proile manager
         */
        void displayProfileManagerButton();

        /*
         * @brief Display the window of the proile manager
         */
        void displayProfileManagerWindow();

        /*
         * @brief Render the ranking of the players of the Endless mode
         */
        void renderRanking();

        /*
         * @brief Render the profile manager of the user
         */
        void renderProfileManager();

      public:
        /*
         * @brief Construct a new Main Menu object
         *
         * @param screenManager The screen manager for asking to render the
         * components
         * @param controller The controller to interact with the server
         */
        MainMenu(MainTui &mainTui, Controller &controller);

        /*
         * @brief Destroy the Main Menu object
         */
        ~MainMenu() = default;

        /*
         * @brief Render the main menu screen with all the components
         */
        void render();
    };

} // namespace TUI

#endif // TUI_MAIN_MENU_HPP
