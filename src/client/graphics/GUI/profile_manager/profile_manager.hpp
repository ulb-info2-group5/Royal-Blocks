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

    /**
    * @brief manage main window of ProfileManager.
    * It allows modify the name, password of actual account.
    */

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
