/*Authors : Ernest Jonas Rafaou*/

#ifndef PROFILE_MANAGER_GUI_HPP
#define PROFILE_MANAGER_GUI_HPP

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>

class Controller;

class MainGui;

class ProfileManagerGui : public QWidget {
    Q_OBJECT

    private:
        Controller &controller_;
        MainGui &mainGui_;

        QStackedWidget *stack_;
        QWidget *mainWidget_;

        QPushButton submit_;
        QPushButton back_;

        QLineEdit newUserName_;
        QLineEdit newPassWord_;

        QLabel changePasswordAndUsernameMsgLabel_;


        // Methode
        void changeName();
        void changePassWord();
        void basicSetup();
        void onBack();

    public:
        ProfileManagerGui(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);

        ~ProfileManagerGui() = default;

    signals:
        // Back to main menu
        void backToMainMenu();
};

#endif // PROFILE_MANAGER_GUI_HPP