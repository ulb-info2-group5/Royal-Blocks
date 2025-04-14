#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <memory>

#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidget>

namespace GUI {

    MainGui::MainGui(Controller &controller, QWidget *parent)
        : QMainWindow(parent), controller_(controller) {
        show();
    }

    void MainGui::run() {
        login_ = std::make_unique<Login>(controller_);
        connect(login_.get(), &Login::loginSuccessful, this,
                &MainGui::showMainMenu);
        login_->run();
        setCentralWidget(login_.get());
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
        login_.reset(); // Login has finish so we don't need it anymore
        mainMenu_ = std::make_unique<MainMenu>(controller_, *this);
        mainMenu_->run();
        setCentralWidget(mainMenu_.get());
    }

} // namespace GUI
