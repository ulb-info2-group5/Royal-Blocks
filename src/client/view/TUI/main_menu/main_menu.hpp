/**
 * @file main_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class declaration file
 * @date 2025-02-12
 * 
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "../../IMain_Menu.hpp"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>

#include <cstdlib>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Controller; // Forward declaration

/**
 * @brief Enum class to represent the state of the main menu
 * 
 */
enum class MainMenuState 
{
    CREATE_GAME,
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
class MainMenu : public IMain_Menu
{
    private:
        /*
        * @brief The screen to use to render the components
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

        /*
        * @brief The controller to ask for the data to show to the user
        */
        Controller *controller_;

        MainMenuState userState_;

        ftxui::Component buttonPlay_;
        ftxui::Component buttonJoinGame_;
        ftxui::Component buttonSendMessagesToFriends_;
        ftxui::Component buttonLookRanking_;
        ftxui::Component buttonManageProfile_;
        ftxui::Component buttonManageFriendsList_;
        ftxui::Component buttonExit_;

        ftxui::Component buttonBack_;

        ftxui::Elements rowsRanking_;

        ftxui::Components friendButtons_;
        ftxui::Component buttonAddFriend_;
        ftxui::Component friendsContainer_;

        // idx 0 : username; idx 1 : password; idx2 : msg
        std::vector<std::string> userInput_;
        ftxui::Component inputChangeUsername_;
        ftxui::Component inputChangePassword_;
        ftxui::Component submitButton_;

        ftxui::Component mainMenuWindow_;
        ftxui::Component rankingWindow_;
        ftxui::Component friendManagerWindow_;
        ftxui::Component profileManagerWindow_;


    protected:

        void displayMainMenuButtons() override;

        void displayMainWindow() override;

        void displayRankingList(const std::vector<std::tuple<int, std::string, int>> &ranking) override;

        void displayRankingWindow(const std::vector<std::tuple<int, std::string, int>> &ranking) override;

        void displayProfileManagerButton() override;

        void displayProfileManagerWindow() override;


    public:
        /*
         * @brief Construct a new Main Menu object
         *
         * @param screen The screen to use to render the components
         */
        MainMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen, Controller *controller);

        /*
         * @brief Destroy the Main Menu object
         */
        ~MainMenu() = default;

        /*
         * @brief Render the main menu screen with all the components
         *
         * @return MainMenuState The state of the main menu
         */
        MainMenuState render();

        /*
         * @brief Render the ranking of the players of the Endless mode
         *
         * @param ranking The ranking of the players of the Endless mode to display,
         * the vector has to be already sorted by the score of the players
         */
         void renderRanking(const std::vector<std::tuple<int, std::string, int>> &ranking) override;

        /*
        *@brief Launch and render the messagingMenu
        *
        *@param friendsList The list of the friends of the user to display
        */
        void renderMessagingMenu(const std::vector<std::string> &friendsList ) override;

        /*
        * @brief Render the profile manager of the user
        */
         void renderProfileManager() override;

        /*
        * @brief Get the user input
        *
        * @return std::vector<std::string> The user input
        */
         std::vector<std::string> getUserNewInput();
};

#endif // MAIN_MENU_HPP

