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
        : QMainWindow(parent), controller_(controller) {}

    void MainGui::run() {
        LoginGui *loginGui = new LoginGui(controller_);
        connect(loginGui, &LoginGui::loginSuccessful, this,
                &MainGui::showMainMenu);
        loginGui->run();
        setCentralWidget(loginGui);
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
        }
    }

    void MainGui::showMainMenu() {
        MainMenuGui *mainMenuGui = new MainMenuGui(controller_, *this);
        mainMenuGui->run();
        setCentralWidget(mainMenuGui);
    }

} // namespace GUI
