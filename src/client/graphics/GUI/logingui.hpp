#ifndef LOGINGUI_HPP
#define LOGINGUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <string>
#include <string_view>
#include "QLabel"

class Controller; // Forward declaration

class LoginGui : public QWidget {
    Q_OBJECT

public:
    explicit LoginGui(Controller *controller, QWidget *parent = nullptr);
    ~LoginGui() = default;

signals:
    void loginSuccessful();

private slots:
    void on_ExitButton_clicked();

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_BackButtonLogin_clicked();

    void on_BackButtonRegister_clicked();

    void on_SendButtonRegister_clicked();

    void on_SendButtonLogin_clicked();

private:
    Controller *controller_;

    QStackedWidget  *stackedWidget_;

    QLineEdit *usernameInputRegister_;
    QLineEdit *passwordInputRegister_;
    QLineEdit *usernameInputLogin_;
    QLineEdit *passwordInputLogin_;

    QWidget *mainPage_;
    QWidget *loginPage_;
    QWidget *registerPage_;

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
    * @brief Create a centered bold title
    * 
    * @param title The title to display
    * @return The QLabel created
    */
    QLabel *createCenterBoldTitle(const std::string_view &title);

    /*
    * @brief Check if the register username and password is valid
    *
    * @return True if the register is valid, false otherwise
    */
    bool isValidRegister();

};

#endif // LOGINGUI_HPP
