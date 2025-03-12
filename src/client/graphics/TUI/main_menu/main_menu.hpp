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

#include "../friends_menu/friends_menu.hpp"
#include "../game_menu/game_menu.hpp"
#include "../messaging/messaging.hpp"

#include <ftxui/component/component.hpp>
#include <string>

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

/**
 * @brief Main menu of the game that will be displayed to the user
 *
 */
class MainMenu final : public IMain_Menu {
  private:
    /*
     * @brief The screen to use to render the components
     */
    ScreenManager &screenManager_;

    /*
     * @brief The controller to ask for the data to show to the user
     */
    Controller &controller_;

    MainMenuState state_;

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
    void handleChoice() override;

    void createMainMenuButtons() override;

    void displayMainWindow() override;

    void displayRankingList() override;

    void displayRankingWindow() override;

    void displayProfileManagerButton() override;

    void displayProfileManagerWindow() override;

    /*
     * @brief Render the ranking of the players of the Endless mode
     */
    void renderRanking() override;

    /*
     * @brief Render the profile manager of the user
     */
    void renderProfileManager() override;

  public:
    /*
     * @brief Construct a new Main Menu object
     *
     * @param screenManager The screen manager for asking to render the
     * components
     * @param controller The controller to interact with the server
     */
    MainMenu(ScreenManager &screenManager, Controller &controller);

    /*
     * @brief Destroy the Main Menu object
     */
    ~MainMenu() = default;

    /*
     * @brief Render the main menu screen with all the components
     */
    void render() override;
};

#endif // MAIN_MENU_HPP
