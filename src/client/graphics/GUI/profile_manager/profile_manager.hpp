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

    class TetrisWindow;

    class ProfileManager : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        TetrisWindow &tetrisWindow_;

        QLineEdit newUserName_;
        QLineEdit newPassWord_;

        std::string errorMessage_;

        // Methode
        void basicSetup();
        void changePasswordUsername();
        bool isValidUsernamePassword();

      private slots:
        void onBack();

      public:
        ProfileManager(Controller &controller, TetrisWindow &tetrisWindow,
                       QWidget *parent = nullptr);

        ~ProfileManager() = default;

      signals:
        // Back to main menu
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_PROFILE_MANAGER_HPP
