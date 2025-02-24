/**
 * @file friends_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsManager class declaration file
 * @date 2025-02-24
 * 
 */

#ifndef FRIENDS_MANAGER_HPP
#define FRIENDS_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <vector>

enum class FriendsManagerState
{
    ADD_FRIEND,
    REMOVE_FRIEND,
    NONE,
    NO,
    BACK,
};

class FriendsManager {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;
        FriendsManagerState state_;
        std::string friendName_;

        /*
        * @brief Render the friends list of the user to display with all friends dislayed is a button
        */
        std::vector<ftxui::Component> displayFriendButtons(const std::vector<std::string> &friendsList);

        /*
        * @brief Manage the friendlist screen when a friend is clicked
        */
        void manageFriendlistScreen(const std::string &friendName);


    public:
        /*
        * @brief Construct a new Friends Manager object
        */
        FriendsManager(std::shared_ptr<ftxui::ScreenInteractive> &screen);

        /*
        * @brief Destroy the Friends Manager object
        */
        ~FriendsManager() = default;

        /*
        * @brief Render the friends manager screen with all the components
        *
        * @param friendsList The list of the friends of the user to display
        * @return FriendsManagerState The state of the friends manager
        */
        FriendsManagerState render(const std::vector<std::string> &friendsList);

        /*
        * @brief Get the name of the friend to add
        *
        * @return std::string The name of the friend to add
        */
        std::string getName() const;

        /*
        * @brief Screen to add a friend
        *
        * @return bool True if the friend will be added, false otherwise
        */
        bool addFriendScreen();

};

#endif