#include "main_menu_gui.hpp"

#include "../qt_config/qt_config.hpp"
#include "../rankinggui/rankinggui.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

MainMenuGui::MainMenuGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller),rankingGui_(controller_) {}


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
    stackedWidget_->setCurrentWidget(&rankingGui_);
}

void MainMenuGui::showMainMenu()
{
    stackedWidget_->setCurrentWidget(&mainMenu_);
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

    createGameButton_.setText("Create a Game");
    createGameButton_.setFixedWidth(500);

    joinGameButton_.setText("Join a Game");
    joinGameButton_.setFixedWidth(500);

    messagesButton_.setText("Messages");
    messagesButton_.setFixedWidth(500);

    rankingButton_.setText("Ranking");
    connect(&rankingButton_, &QPushButton::clicked, this, &MainMenuGui::on_RankingButton_clicked);
    rankingButton_.setFixedWidth(500);

    manageProfileButton_.setText("Manage Profile");
    manageProfileButton_.setFixedWidth(500);

    manageFriendsListButton_.setText("Manage Friends List");
    manageFriendsListButton_.setFixedWidth(500);

    quitGameButton_.setText("Quit Game");
    quitGameButton_.setFixedWidth(500);
    connect(&quitGameButton_, &QPushButton::clicked, this, &MainMenuGui::on_QuitGameButton_clicked);


    QVBoxLayout *menu = new QVBoxLayout();
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    menu->addWidget(createCenterBoldTitle("Welcome to the main menu of Tetris Royal !"));
    menu->addWidget(&createGameButton_, 0, Qt::AlignCenter);
    menu->addWidget(&joinGameButton_, 0, Qt::AlignCenter);
    menu->addWidget(&messagesButton_, 0, Qt::AlignCenter);
    menu->addWidget(&rankingButton_, 0, Qt::AlignCenter);
    menu->addWidget(&manageProfileButton_, 0, Qt::AlignCenter);
    menu->addWidget(&manageFriendsListButton_, 0, Qt::AlignCenter);
    menu->addWidget(&quitGameButton_, 0, Qt::AlignCenter);
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    mainMenu_.setLayout(menu);
    stackedWidget_->addWidget(&mainMenu_);

    connect(&rankingGui_, &RankingGui::backToMainMenu, this, &MainMenuGui::showMainMenu);
    stackedWidget_->addWidget(&rankingGui_);
}

