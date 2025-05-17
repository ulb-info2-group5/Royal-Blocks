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

#ifndef GUI_LOGIN_HPP
#define GUI_LOGIN_HPP

#include <string>

#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <QLabel>

class Controller;

namespace GUI {

    class Login : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;

        QStackedWidget stackedWidget_;

        QLineEdit *usernameInputRegister_;
        QLineEdit *passwordInputRegister_;
        QLineEdit *usernameInputLogin_;
        QLineEdit *passwordInputLogin_;
        QLineEdit *ipInput_;
        QLineEdit *portInput_;

        QLabel connectionToServerLabel_;

        QPushButton *sendButtonRegister_;
        QPushButton *sendButtonLogin_;

        std::string errorMessage_;

        /*
         * @brief Action to perform when exiting the application for the eit at
         * the login or at the main menu to quit the game
         */
        void actionOnExit();

        /*
         * @brief Clear the inputs of the user
         */
        void clearInputs();

        /*
         * @brief Check if the register username and password is valid
         *
         * @return True if the register is valid, false otherwise
         */
        bool isValidRegister();

        /*
         * @brief Setup the Login Gui
         */
        void setup();

        QString getConnectedMessage() const;

        /*
        * @brief Update the connected message draw on the main page
        */
        void updateConnectedMessage();

      private slots:
        /*
         * @brief Action to perform when exiting the application
         */
        void on_ExitButton_clicked();

        /*
         * @brief Action to perform when the user click on the login button
         */
        void on_LoginButton_clicked();

        /*
         * @brief Action to perform when the user click on the register button
         */
        void on_RegisterButton_clicked();

        /*
         * @brief Action to perform when the user click on the back button
         */
        void on_BackButton_clicked();

        /*
         * @brief Action to perform when the user click on the send button in
         * the register page
         */
        void on_SendButtonRegister_clicked();

        /*
         * @brief Action to perform when the user click on the send button in
         * the login page
         */
        void on_SendButtonLogin_clicked();

        /*
         * @brief Action to perform when the user click on the enter key in the
         * username input
         */
        void on_UsernameInputRegister_EnterPressed();

        /*
         * @brief Action to perform when the user click on the enter key in the
         * username input
         */
        void on_UsernameInputLogin_EnterPressed();

        /*
         * @brief Action to perform when the user click on the enter key in the
         * password input
         */
        void on_PasswordInputRegister_EnterPressed();

        /*
         * @brief Action to perform when the user click on the enter key in the
         * password input
         */
        void on_PasswordInputLogin_EnterPressed();

        /*
         * @brief Action to perform when the user click on the choose ip and port button
         */
        void on_ChooseIpPortButton_clicked();

        /*
         * @brief Action to perform when the user click on the connect button
         */
        void on_ConnectButton_clicked();

      public:
        Login(Controller &controller, QWidget *parent = nullptr);

        ~Login() = default;

        /*
         * @brief Run the login Gui
         */
        void run();

      signals:
        /*
         * @brief Signal emitted when the login is successful
         */
        void loginSuccessful();

        /*
         * @brief Signal emitted when the user click on the quit game button
         */
        void quitGame();
    };

} // namespace GUI

#endif // GUI_LOGIN_HPP
