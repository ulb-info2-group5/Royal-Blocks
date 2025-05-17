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

#ifndef TUI_LOGIN_INPUT_HPP
#define TUI_LOGIN_INPUT_HPP

#include <ftxui/component/component.hpp>
#include <string>

class Controller;

namespace TUI {

    class MainTui;

    enum class LoginType {
        LOGIN,
        REGISTER,
        NONE,
    };

    enum class LoginState {
        SUBMIT,
        BACK,
        NONE,
    };

    /**
     * @brief LoginInput class to get the login input or register input from the
     * user
     *
     */
    class LoginInput final {
      private:
        /*
         * @brief The screen to use to render the components
         */
        MainTui &mainTui_;

        /*
         * @brief The controller to ask for the data to show to the user
         */
        Controller &controller_;

        /*
         * @brief The title of the input screen (Login or Register)
         */
        std::string title_;

        /*
         * @brief The type of the login (Login or Register)
         */
        LoginType loginType_;

        /*
         * @brief The state of the login input
         */
        LoginState loginState_;

        /*
         * @brief The username of the user
         */
        std::string username_;

        /*
         * @brief The password of the user
         */
        std::string password_;

        /*
         * @brief The instruction to show to the user
         */
        std::string instruction_;

        /*
         * @brief The custom message to show to the user
         */
        std::string message_;

        std::string errorMessage_;

        ftxui::Component buttonSubmit_;
        ftxui::Component buttonBack_;
        ftxui::Component inputUsername_;
        ftxui::Component inputPassword_;
        ftxui::Component displayWindow_;

        /*
         * @brief Create the Button Back component with the action to go back
         */
        void createButtonBack();

        /*
         * @brief Create the Button Submit component with the action for submit
         */
        void createButtonSubmit();

        /*
         * @brief Display the window of the login/register input
         */
        void displayWindow();

        /*
         * @brief Check if the username and password are valid to create an
         * account
         *
         * @return true if the username and password are valid, false otherwise
         */
        bool isValidUsernamePassword();

      public:
        /*
         * @brief Construct a new Login Input object
         *
         * @param MainTui The Main Tui for asking to render the
         * components
         * @param controller The controller to interact with the server
         * @param title The title of the input screen (Login or Register)
         * @param loginType The type of the login (Login or Register)
         */
        LoginInput(MainTui &MminTui, Controller &controller, std::string title,
                   LoginType loginType);

        /*
         * @brief Destroy the Login Input object
         */
        ~LoginInput() = default;

        /*
         * @brief Render the login input screen with all the components
         *
         * @return LoginState The state of the login input
         */
        LoginState render();

        /*
         * @brief Add an instruction to show to the user
         *
         * @param string instruction the instruction to show
         */
        void addInstruction(const std::string_view instruction);

        /*
         * @brief Add a message to show to the user
         *
         * @param string message the message to show
         */
        void addMessage(const std::string_view message);

        /*
         * @brief Clear the info of the user input (username and password)
         */
        void clearInfo();
    };

} // namespace TUI

#endif // TUI_LOGIN_INPUT_HPP
