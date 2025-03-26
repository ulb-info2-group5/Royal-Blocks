#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"

#include "rankinggui/rankinggui.hpp"
#include "logingui/logingui.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

MainGui::MainGui(QWidget *parent, Controller *controller)
    : QMainWindow(parent), controller_(controller) {}


void MainGui::run()
{
    LoginGui *loginGui = new LoginGui(controller_);
    loginGui->run();
    setCentralWidget(loginGui);
}

void MainGui::forceRefresh()
{
    this->update();
}

void MainGui::showMainMenu()
{
    // TODO: run the main menu
}
