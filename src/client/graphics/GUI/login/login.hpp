#ifndef GUI_LOGIN_HPP
#define GUI_LOGIN_HPP

#include <string>

#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class Controller;

namespace GUI {

    class Login : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;

        QStackedWidget stackedWidget_;

        QLineEdit usernameInputRegister_;
        QLineEdit passwordInputRegister_;
        QLineEdit usernameInputLogin_;
        QLineEdit passwordInputLogin_;
        QLineEdit ipInput_;
        QLineEdit portInput_;

        QPushButton sendButtonRegister_;
        QPushButton sendButtonLogin_;

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
    };

} // namespace GUI

#endif // GUI_LOGIN_HPP
