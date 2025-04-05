/*Authors : Ernest Jonas Rafaou*/

#ifndef GUI_PROFILE_MANAGER_HPP
#define GUI_PROFILE_MANAGER_HPP

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class Controller;

namespace GUI {

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
        void basicSetup();
        void changePasswordUsername();

      private slots:
        void onBack();

      public:
        ProfileManagerGui(Controller &controller, MainGui &mainGui,
                          QWidget *parent = nullptr);

        ~ProfileManagerGui() = default;

      signals:
        // Back to main menu
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_PROFILE_MANAGER_HPP
