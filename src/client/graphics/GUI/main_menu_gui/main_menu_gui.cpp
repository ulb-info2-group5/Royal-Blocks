#include "main_menu_gui.hpp"

#include "../qt_config/qt_config.hpp"
#include "../rankinggui/rankinggui.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

MainMenuGui::MainMenuGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {}


void MainMenuGui::run() {
    setup();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget_);
    setLayout(layout);

    show();
}

void MainMenuGui::on_QuitGameButton_clicked()
{
    actionOnExit();
}

void MainMenuGui::on_RankingButton_clicked()
{
    rankingGui_ = new RankingGui(controller_);
    connect(rankingGui_, &RankingGui::backToMainMenu, this, &MainMenuGui::showMainMenu);
    stackedWidget_->addWidget(rankingGui_);
    stackedWidget_->setCurrentWidget(rankingGui_);
}

void MainMenuGui::showMainMenu()
{
    rankingGui_->deleteLater();
    stackedWidget_->setCurrentWidget(mainMenu_);
}

/*---------------------------------------------
                Private Methods
----------------------------------------------*/


void MainMenuGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainMenuGui::setup() {
    stackedWidget_ = new QStackedWidget();

    QPushButton *createGameButton = new QPushButton("Create a Game");
    createGameButton->setFixedWidth(500);

    QPushButton *joinGameButton = new QPushButton("Join a Game");
    joinGameButton->setFixedWidth(500);

    QPushButton *messagesButton = new QPushButton("Messages");
    messagesButton->setFixedWidth(500);

    QPushButton *rankingButton = new QPushButton("Ranking");
    connect(rankingButton, &QPushButton::clicked, this, &MainMenuGui::on_RankingButton_clicked);
    rankingButton->setFixedWidth(500);

    QPushButton *manageProfileButton = new QPushButton("Manage Profile");
    manageProfileButton->setFixedWidth(500);

    QPushButton *manageFriendsListButton = new QPushButton("Manage Friends List");
    manageFriendsListButton->setFixedWidth(500);

    QPushButton *quitGameButton = new QPushButton("Quit Game");
    quitGameButton->setFixedWidth(500);
    connect(quitGameButton, &QPushButton::clicked, this, &MainMenuGui::on_QuitGameButton_clicked);


    QVBoxLayout *menu = new QVBoxLayout();
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    menu->addWidget(createCenterBoldTitle("Welcome to the main menu of Tetris Royal !"));
    menu->addWidget(createGameButton, 0, Qt::AlignCenter);
    menu->addWidget(joinGameButton, 0, Qt::AlignCenter);
    menu->addWidget(messagesButton, 0, Qt::AlignCenter);
    menu->addWidget(rankingButton, 0, Qt::AlignCenter);
    menu->addWidget(manageProfileButton, 0, Qt::AlignCenter);
    menu->addWidget(manageFriendsListButton, 0, Qt::AlignCenter);
    menu->addWidget(quitGameButton, 0, Qt::AlignCenter);
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    mainMenu_ = new QWidget();
    mainMenu_->setLayout(menu);
    stackedWidget_->addWidget(mainMenu_);
}

