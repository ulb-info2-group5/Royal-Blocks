#ifndef GUI_TETRIS_WINDOW_HPP
#define GUI_TETRIS_WINDOW_HPP

#include "../../core/controller/update_type.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"
#include "qt_config/qt_config.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QStackedWidget>
#include <QStyleFactory>

enum class UpdateType;

namespace GUI {

    class TetrisWindow : public QMainWindow {
        Q_OBJECT

      private:
        Login *login_;

        MainMenu *mainMenu_;

        QSettings settings_;

        void setDarkMode() {
            qApp->setStyle(QStyleFactory::create("Fusion"));
            qApp->setPalette(createDarkPalette());
            qApp->setStyleSheet(
                "QToolTip { color: white; background-color: black; "
                "border: 1px solid white; }");
            QSettings settings("Royal Tetris", "Royal Tetris");
            settings.setValue("theme/darkMode", true);
        }

        void setLightMode() {
            qApp->setStyle(QStyleFactory::create("Fusion"));
            qApp->setPalette(createLightPalette());
            qApp->setStyleSheet(
                "QToolTip { color: black; background-color: white; "
                "border: 1px solid black; }");
            QSettings settings("Royal Tetris", "Royal Tetris");
            settings.setValue("theme/darkMode", false);
        }

      public:
        TetrisWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
            QSettings settings("Royal Tetris", "Royal Tetris");
            if (settings.value("theme/darkMode", true).toBool()) {
                setDarkMode();
            } else {
                setLightMode();
            }

            setMinimumSize(600, 500);
            showMaximized();
            setWindowTitle("Tetris Royal");

            show();
        }

        void forceRefresh(UpdateType updateType) {
            if (updateType == UpdateType::FRIENDS_LIST) {
                emit updateFriendsList();
            } else if (updateType == UpdateType::FRIEND_REQUESTS) {
                emit updateFriendRequestsList();
            } else if (updateType == UpdateType::RANKING) {
                emit updateRanking();
            } else if (updateType == UpdateType::CONVERSATIONS) {
                emit updateConversations();
            } else if (updateType == UpdateType::GAME_STATE) {
                emit updateGameState();
            }
        }

        /*
         * @brief Show the main menu page
         */
        void showMainMenu() {
            if (login_) {
                login_->deleteLater(); // Delete login because we don't need it
                                       // anymore
            }
            mainMenu_->run();
            this->setCentralWidget(mainMenu_);
            connect(mainMenu_, &MainMenu::quitGame, this,
                    &TetrisWindow::quitGui);

            connect(mainMenu_, &MainMenu::applyDarkTheme, this,
                    &TetrisWindow::setDarkMode);
            connect(mainMenu_, &MainMenu::applyLightTheme, this,
                    &TetrisWindow::setLightMode);
        }

        void run(Controller &controller) {
            login_ = new Login(controller);
            login_->run();

            mainMenu_ = new MainMenu(controller, *this);

            this->setCentralWidget(login_);
            connect(login_, &Login::loginSuccessful, this,
                    &TetrisWindow::showMainMenu);
        }

        /*
         * @brief Action to perform when exiting the gui
         */
        void quitGui() {
            QMessageBox::StandardButton confirmExit;
            confirmExit = QMessageBox::question(
                this, "Quit", "Are you sure you want to quit the game ?",
                QMessageBox::Yes | QMessageBox::No);
            if (confirmExit == QMessageBox::Yes) {
                QApplication::quit();
            }
        }

      signals:
        /*
         * @brief Signal to update the friends list
         */
        void updateFriendsList();

        /*
         * @brief Signal to update the friend requests list
         */
        void updateFriendRequestsList();

        /*
         * @brief Signal to update the ranking
         */
        void updateRanking();

        /*
         * @brief Signal to update the conversations
         */
        void updateConversations();

        /*
         * @brief Signal to update the game state
         */
        void updateGameState();
    };

} // namespace GUI

#endif // GUI_TETRIS_WINDOW_HPP
