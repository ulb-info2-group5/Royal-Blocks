#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"

#include "logingui/logingui.hpp"
#include "main_menu_gui/main_menu_gui.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

MainGui::MainGui(QWidget *parent, Controller *controller)
    : QMainWindow(parent), controller_(controller) {}


void MainGui::run()
{
    LoginGui *loginGui = new LoginGui(*controller_);
    connect(loginGui, &LoginGui::loginSuccessful, this, &MainGui::showMainMenu);
    loginGui->run();
    setCentralWidget(loginGui);
}

void MainGui::forceRefresh(UpdateType updateType)
{
    if (updateType == UpdateType::FRIENDS_LIST) {
        emit updateFriendsList();
    } else if (updateType == UpdateType::FRIEND_REQUESTS) {
        emit updateFriendRequestsList();
    }
}

void MainGui::showMainMenu()
{
    MainMenuGui *mainMenuGui = new MainMenuGui(*controller_, this);
    mainMenuGui->run();
    setCentralWidget(mainMenuGui);
}
