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
};

#endif // CONTROLLER_HPP