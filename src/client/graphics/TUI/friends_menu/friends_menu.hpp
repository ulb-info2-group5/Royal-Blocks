/**
 * @file friends_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsMenu class declaration file
 * @date 2025-02-24
 *
 */

#ifndef TUI_FRIENDS_MENU_HPP
#define TUI_FRIENDS_MENU_HPP

#include "../../../../common/bindings/user.hpp"

#include <ftxui/component/component.hpp>
#include <vector>

class Controller;

namespace TUI {

    class MainTui;

    enum class FriendsManagerState {
        ADD_FRIEND,
        REMOVE_FRIEND,
        NONE,
        NO,
        BACK,
    };

    class FriendsMenu final {
      private:
        MainTui &mainTui_;
        Controller &controller_;
        std::string friendNameBuffer_;
        bool exit_; // Boolean to exit the friends menu

        ftxui::Component buttonBack_;
        ftxui::Component buttonAddFriend_;
        ftxui::Component input_;
        ftxui::Component submitButton_;
        ftxui::Component buttonBackToMainMenu_;
        ftxui::Component ManageFriendRequest_;

        std::string addMessage_;

        /*
         * @brief Render the friends list of the user to display with all
         * friends dislayed is a button
         *
         * @param friendsList The list of friends to display
         * @return std::vector<ftxui::Component> The list of buttons to display
         */
        std::vector<ftxui::Component>
        displayFriendButtons(const std::vector<bindings::User> &friendsList);

        /*
         * @brief Manage the friendlist screen when a friend is clicked
         *
         * @param friendUser The friend to manage
         * friend
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

        /*
         * @brief Screen accept or decline a friend in the friend request screen
         */
        void FriendRequestScreen();

      public:
        /*
         * @brief Construct a new Friends Manager object
         *
         * @param mainnTui The Main Tui for asking to render the
         * components
         * @param controller The controller to interact with the server
         */
        FriendsMenu(MainTui &mainTui, Controller &controller);

        /*
         * @brief Destroy the Friends Manager object
         */
        ~FriendsMenu() = default;

        /*
         * @brief Render the friends manager screen with all the components
         */
        void render();
    };

} // namespace TUI

#endif // TUI_FRIENDS_MENU_HPP
