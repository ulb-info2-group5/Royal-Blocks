#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"

#include "rankinggui/rankinggui.hpp"
#include "logingui/logingui.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

MainGui::MainGui(QWidget *parent, Controller *controller)
    : QMainWindow(parent)
    , controller_(controller)
{
    stackedWidget_ = new QStackedWidget();

    LoginGui *loginPage = new LoginGui(controller_);
    connect(loginPage, &LoginGui::loginSuccessful, this, &MainGui::showMainMenu);
    
    stackedWidget_->addWidget(loginPage);
    stackedWidget_->setCurrentWidget(loginPage);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget_);
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    this->show();
}

void MainGui::forceRefresh()
{
    this->update();
}

void MainGui::showMainMenu()
{
    stackedWidget_->setCurrentIndex(3); // Main Menu page
}

void MainGui::on_QuitGameButton_clicked()
{
    actionOnExit();
}

void MainGui::on_RankingButton_clicked()
{
    RankingGui *rankingPage = new RankingGui(controller_);

    connect(rankingPage, &RankingGui::backToMainMenu, this, &MainGui::on_BackToMainMenu_clicked);

    stackedWidget_->addWidget(rankingPage);
    stackedWidget_->setCurrentWidget(rankingPage);
}

void MainGui::on_BackToMainMenu_clicked()
{
    stackedWidget_->setCurrentIndex(3); // Main Menu page
}

/*--------------------------------------------
                PRIVATE METHODS
--------------------------------------------*/

void MainGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}