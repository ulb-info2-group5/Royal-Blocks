#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"

#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidget>
#include <memory>

namespace GUI {

    MainGui::MainGui(Controller &controller, QWidget *parent)
        : QMainWindow(parent), controller_(controller) {
        showFullScreen();
    }

    void MainGui::run() {
        loginGui_ = std::make_unique<LoginGui>(controller_);
        connect(loginGui_.get(), &LoginGui::loginSuccessful, this,
                &MainGui::showMainMenu);
        loginGui_->run();
        setCentralWidget(loginGui_.get());
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
        loginGui_.reset(); // Login has finish so we don't need it anymore
        mainMenuGui_ = std::make_unique<MainMenuGui>(controller_, *this);
        mainMenuGui_->run();
        setCentralWidget(mainMenuGui_.get());
    }

} // namespace GUI
