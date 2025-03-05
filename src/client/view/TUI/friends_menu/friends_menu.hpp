/**
 * @file friends_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsMenu class declaration file
 * @date 2025-02-24
 *
 */

#ifndef FRIENDS_MENU_HPP
#define FRIENDS_MENU_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <vector>

class Controller; // Forward declaration

enum class FriendsManagerState {
    ADD_FRIEND,
    REMOVE_FRIEND,
    NONE,
    NO,
    BACK,
};

class FriendsMenu {
  private:
    ftxui::ScreenInteractive &screen_;
    Controller *controller_;
    std::string friendName_;
    std::string msg_; // Message to display on the adding friends menu

    ftxui::Component buttonBack_;
    ftxui::Component buttonAddFriend_;
    ftxui::Component input_;
    ftxui::Component submitButton_;

    /*
     * @brief Render the friends list of the user to display with all friends
     * dislayed is a button
     */
    std::vector<ftxui::Component>
    displayFriendButtons(const std::vector<std::string> &friendsList);

    /*
     * @brief Manage the friendlist screen when a friend is clicked
     */
    void manageFriendlistScreen(const std::string &friendName);

    /*
     * @brief Screen to add a friend
     */
    void addFriendScreen();

  public:
    /*
     * @brief Construct a new Friends Manager object
     */
     FriendsMenu(ftxui::ScreenInteractive &screen,
                   Controller *controller);

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