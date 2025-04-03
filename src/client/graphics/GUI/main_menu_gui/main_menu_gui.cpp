#include "main_menu_gui.hpp"

#include "../qt_config/qt_config.hpp"
#include "../friends_menu_gui/friends_menu_gui.hpp"
#include "../message_menu_gui/message_menu_gui.hpp"
#include "../game_menu_gui/game_menu_gui.hpp"
#include "../main_gui.hpp"
#include "../profile_manager/profile_manager_gui.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

MainMenuGui::MainMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), rankingGui_(controller_, mainGui), QWidget(parent), friendsMenuGui_(controller, mainGui), messageMenuGui_(controller, mainGui), gameMenuGui_(controller, mainGui), profileManagerGui_(controller,mainGui) {}

void MainMenuGui::run() {
    setup();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget_);
    setLayout(layout);

    show();
}

void MainMenuGui::on_QuitGameButton_clicked() {
    actionOnExit();
}

void MainMenuGui::on_RankingButton_clicked() {
    stackedWidget_->setCurrentWidget(&rankingGui_);
}

void MainMenuGui::on_ManageFriendsListButton_clicked() {
    stackedWidget_->setCurrentWidget(&friendsMenuGui_);
}

void MainMenuGui::on_MessagesButton_clicked() {
    stackedWidget_->setCurrentWidget(&messageMenuGui_);
}

void MainMenuGui::on_CreateGameButton_clicked() {
    gameMenuGui_.run(true);
    stackedWidget_->setCurrentWidget(&gameMenuGui_);
}

void MainMenuGui::on_JoinGameButton_clicked() {
    gameMenuGui_.run(false);
    stackedWidget_->setCurrentWidget(&gameMenuGui_);
}

void MainMenuGui::showMainMenu() {
    stackedWidget_->setCurrentWidget(&mainMenu_);
}

void MainMenuGui::on_ProfileManager_clicked() {
    stackedWidget_->setCurrentWidget(&profileManagerGui_);
}

/*---------------------------------------------
                Private Methods
----------------------------------------------*/


void MainMenuGui::actionOnExit() {
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to quit the game ?",
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
    connect(&messagesButton_, &QPushButton::clicked, this, &MainMenuGui::on_MessagesButton_clicked);
    messagesButton_.setFixedWidth(500);

    rankingButton_.setText("Ranking");
    connect(&rankingButton_, &QPushButton::clicked, this, &MainMenuGui::on_RankingButton_clicked);
    rankingButton_.setFixedWidth(500);

    manageProfileButton_.setText("Manage Profile");
    manageProfileButton_.setFixedWidth(500);

    manageFriendsListButton_.setText("Manage Friends List");
    connect(&manageFriendsListButton_, &QPushButton::clicked, this, &MainMenuGui::on_ManageFriendsListButton_clicked);
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

    connect(&friendsMenuGui_, &FriendsMenuGui::backToMainMenu, this, &MainMenuGui::showMainMenu);
    stackedWidget_->addWidget(&friendsMenuGui_);

    connect(&messageMenuGui_, &MessageMenuGui::backToMainMenu, this, &MainMenuGui::showMainMenu);
    stackedWidget_->addWidget(&messageMenuGui_);

    connect(&createGameButton_, &QPushButton::clicked, this, &MainMenuGui::on_CreateGameButton_clicked);
    connect(&joinGameButton_, &QPushButton::clicked, this, &MainMenuGui::on_JoinGameButton_clicked);
    connect(&gameMenuGui_, &GameMenuGUI::backToMainMenu, this, &MainMenuGui::showMainMenu);
    stackedWidget_->addWidget(&gameMenuGui_);
}
