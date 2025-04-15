#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidget>

namespace GUI {

    MainGui::MainGui(Controller &controller, QWidget *parent)
        : QMainWindow(parent), controller_(controller) {
        setWindowTitle("Tetris Royal");
        setMinimumSize(500, 500);
        showMaximized();
    }

    void MainGui::run() {
        login_ = new Login(controller_);
        login_->run();
        setCentralWidget(login_);
        connect(login_, &Login::loginSuccessful, this,
                &MainGui::showMainMenu);
    }

    void MainGui::forceRefresh(UpdateType updateType) {
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

    void MainGui::showMainMenu() {
        if (login_) {
            login_->deleteLater(); // Delete login because we don't need it anymore
        }
        mainMenu_ = new MainMenu(controller_, *this);
        mainMenu_->run();
        setCentralWidget(mainMenu_);
        connect(mainMenu_, &MainMenu::quitGame, this,
                &MainGui::quitGui);
    }

    void MainGui::quitGui() {
        QMessageBox::StandardButton confirmExit;
        confirmExit = QMessageBox::question(
            this, "Quit", "Are you sure you want to quit the game ?",
            QMessageBox::Yes | QMessageBox::No);
        if (confirmExit == QMessageBox::Yes) {
            QApplication::quit();
        }
    }

} // namespace GUI
