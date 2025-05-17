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

#ifndef TUI_LOGIN_MENU_HPP
#define TUI_LOGIN_MENU_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>

#include "../login_input/login_input.hpp"

class Controller;

namespace TUI {

    class MainTui;

    enum class LoginResult {
        SUCCESS,
        EXIT,
    };

    enum class Login {
        LOGGED,
        EXIT,
        NONE,
    };

    /**
     * @brief LoginMenu class to show the login menu screen with choices to
     * login or register
     *
     */
    class LoginMenu final {
      private:
        /*
         * @brief The screen to use to render the components
         */
        MainTui &mainTui_;

        /*
         * @brief The controller to ask for the data to show to the user
         */
        Controller &controller_;

        LoginInput loginInput_;

        LoginInput registerInput_;

        Login loginState_;

        LoginState userState_;

        bool showIpPortMenu_;

        std::string ip_;
        std::string port_;
        std::string errorConnectionMessage_;
        std::string connectionMessage_;
        std::string errorPortMessage_;

        ftxui::Component buttonRegister_;
        ftxui::Component buttonLogin_;
        ftxui::Component buttonExit_;
        ftxui::Component buttonChooseIpPort_;
        ftxui::Component buttonBack_;
        ftxui::Component buttonConnect_;

        ftxui::Component ipInput_;
        ftxui::Component portInput_;

        ftxui::Component displayWindow_;

        ftxui::Component mainMenu_;
        ftxui::Component ipPortMenu_;
        ftxui::Component tabContainer_;
        int selectedMenuIndex_ = 0;


        /*
         * @brief Create the buttons and inputs needed for the login menu
         */
        void createButtonsInputs();

        /*
         * @brief Display the window of the login menu with all the components
         */
        void displayWindow();

        /*
         * @brief Get connection info from input and send it to the controller to 
         * try to connect to the server
         */
        void checkConnection();

        /*
         * @brief Update the connection message to show if the connection is
         * successful or not
         */
        void updateConnectedMessage();

        /*
         * @brief Create the colored connection message to show to the user
         *
         * @return ftxui::Element The element to render
         */
        ftxui::Element coloredConnectionMessage() const;


      public:
        /*
         * @brief Construct a new Login Menu object
         *
         * @param screenManager The screen manager for asking to render the
         * components
         * @param controller The controller to interact with the server
         */
        LoginMenu(MainTui &screenManager, Controller &controller);

        /*
         * @brief Destroy the Login Menu object
         */
        ~LoginMenu() = default;

        /*
         * @brief Render the login menu screen with all the components
         *
         * @return LoginResult The result if login succeed or want to exit the
         * program
         */
        LoginResult render();
    };

} // namespace TUI

#endif // TUI_LOGIN_MENU_HPP
