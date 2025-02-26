/**
 * @file controller.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class header file
 * @date 2025-02-24
 * 
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../network/network_manager.hpp"
#include "../view/TUI/screen_manager.hpp"
#include <string>
#include <vector>

class Controller {
    private:
        /*
        * @brief The network manager to manage the connection with the server
        */
        NetworkManager networkManager_;

        /*
        * @brief The screen manager to manage the screens to show to the user
        */
        ScreenManager screenManager_;

    public:

        /*
        * @brief Construct a new Controller object
        */
        Controller();

        /*
        * @brief Destroy the Controller object
        */
        ~Controller();

        /*
        * @brief Run the controller to manage the game
        */
        void run();

        /*
        * @brief Verify and create the account by communicate with the server
        *
        * @param username The username of the user
        * @param password The password of the user
        * @return true If the account is created, false otherwise
        */
        bool verifyRegister(const std::string &username, const std::string &password) const;

        /*
        * @brief Verify the username and password of the user is correct
        *
        * @param username The username of the user
        * @param password The password of the user
        * @return true If the username and password are correct, false otherwise
        */
        bool verifyLogin(const std::string &username, const std::string &password) const;

        /*
        * @brief Get the ranking of the players of the Endless mode
        *
        * @return std::vector<std::tuple<int, std::string, int>> The ranking of the players of the Endless mode
        */
        std::vector<std::tuple<int, std::string, int>> getRanking() const;

        /*
        * @brief Change the profile of the user by changing the username and password
        *
        * @param username The new username of the user
        * @param password The new password of the user
        * @return true If the profile is changed, false otherwise
        */
        bool changeProfile(const std::string &username, const std::string &password) const;

        /*
        * @brief Get the friends list of the user
        *
        * @return std::vector<std::string> The friends list of the user
        */
        std::vector<std::string> getFriendsList() const;

        /*
        * @brief Add a friend to the friends list of the user
        *
        * @param friendName The name of the friend to add
        * @return true If the friend is added, false otherwise
        */
        bool addFriend(const std::string &friendName) const;


        /*
        * @brief Remove a friend from the friends list of the user
        *
        * @param friendName The name of the friend to remove
        * @return true If the friend is removed, false otherwise
        */
        bool removeFriend(const std::string &friendName) const;
    };


#endif // CONTROLLER_HPP