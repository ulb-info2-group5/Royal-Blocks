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

        /*
        * @brief Handle the login menu to show to the user
        */
        void handleLoginMenu();

        /*
        * @brief Handle the input menu to show to the user
        *
        * @param type The type of the input menu
        */
        void handleInputMenu(const InputType type);

        /*
        * @brief Handle the main menu to show to the user
        *
        * @return MainMenuState The state of the main menu
        */
        MainMenuState handleMainMenu();

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
};

#endif // CONTROLLER_HPP