#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"

#include "logingui/logingui.hpp"
#include "main_menu_gui/main_menu_gui.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

MainGui::MainGui(Controller &controller, QWidget *parent)
    : controller_(controller), QMainWindow(parent) {}


void MainGui::run() {
    LoginGui *loginGui = new LoginGui(controller_);
    connect(loginGui, &LoginGui::loginSuccessful, this, &MainGui::showMainMenu);
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
    }
}

void MainGui::showMainMenu() {
    MainMenuGui *mainMenuGui = new MainMenuGui(controller_, *this);
    mainMenuGui->run();
    setCentralWidget(mainMenuGui);
}
