#ifndef LOGINGUI_HPP
#define LOGINGUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <qglobal.h>
#include <string>

class Controller; // Forward declaration

class LoginGui : public QWidget {
    Q_OBJECT

    private:
        Controller &controller_;

        QStackedWidget  *stackedWidget_;

        QLineEdit usernameInputRegister_;
        QLineEdit passwordInputRegister_;
        QLineEdit usernameInputLogin_;
        QLineEdit passwordInputLogin_;

        QWidget *mainPage_;
        QWidget *loginPage_;
        QWidget *registerPage_;

        QPushButton exitButton_;
        QPushButton loginButton_;
        QPushButton registerButton_;
        QPushButton backButtonLogin_;
        QPushButton backButtonRegister_;
        QPushButton sendButtonRegister_;
        QPushButton sendButtonLogin_;

        std::string errorMessage_;

        /*
        * @brief Action to perform when exiting the application for the eit at the login or at the main menu to quit the game
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
        * @brief Action to perform when the user click on the back button in the login page
        */
        void on_BackButtonLogin_clicked();

        /*
        * @brief Action to perform when the user click on the back button in the register page
        */
        void on_BackButtonRegister_clicked();

        /*
        * @brief Action to perform when the user click on the send button in the register page
        */
        void on_SendButtonRegister_clicked();

        /*
        * @brief Action to perform when the user click on the send button in the login page
        */
        void on_SendButtonLogin_clicked();

    public:
        LoginGui(Controller &controller, QWidget *parent = nullptr);
        
        ~LoginGui() = default;

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

#endif // LOGINGUI_HPP
