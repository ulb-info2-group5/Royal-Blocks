/**
 * @file friends_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsMenu class declaration file
 * @date 2025-02-24
 *
 */

#ifndef FRIENDS_MENU_HPP
#define FRIENDS_MENU_HPP

#include "../../../../common/bindings/user.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

enum class FriendsManagerState {
    ADD_FRIEND,
    REMOVE_FRIEND,
    NONE,
    NO,
    BACK,
};

class FriendsMenu final {
  private:
    ScreenManager &screenManager_;
    Controller &controller_;
    std::string friendNameBuffer_;
    bool exit_; // Boolean to exit the friends menu

    ftxui::Component buttonBack_;
    ftxui::Component buttonAddFriend_;
    ftxui::Component input_;
    ftxui::Component submitButton_;
    ftxui::Component buttonBackToMainMenu_;

    /*
     * @brief Render the friends list of the user to display with all friends
     * dislayed is a button
     */
    std::vector<ftxui::Component>
    displayFriendButtons(const std::vector<bindings::User> &friendsList);

    /*
     * @brief Manage the friendlist screen when a friend is clicked
     */
    void manageFriendlistScreen(const bindings::User &friendUser);

    /*
     * @brief Screen to add a friend
     */
    void addFriendScreen();

    /*
     * @brief Create the buttons of the friends manager
     */
    void createButtons();

  public:
    /*
     * @brief Construct a new Friends Manager object
     *
     * @param screenManager The screen manager for asking to render the components
     * @param controller The controller to interact with the server
     */
    FriendsMenu(ScreenManager &screenManager, Controller &controller);

    /*
     * @brief Destroy the Friends Manager object
     */
    ~FriendsMenu() = default;

    /*
     * @brief Render the friends manager screen with all the components
     */
    void render();
};

#endif
