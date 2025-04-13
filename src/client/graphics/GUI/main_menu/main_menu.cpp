#include "main_menu.hpp"

#include "../friends_menu/friends_menu.hpp"
#include "../game_menu/game_menu.hpp"
#include "../main_gui.hpp"
#include "../message_menu/message_menu.hpp"
#include "../profile_manager/profile_manager.hpp"
#include "../qt_config/qt_config.hpp"
#include "graphics/GUI/game_display/game_display.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

namespace GUI {

    MainMenuGui::MainMenuGui(Controller &controller, MainGui &mainGui,
                             QWidget *parent)
        : QWidget(parent), controller_(controller),
          rankingGui_(controller_, mainGui), gameMenu_(controller, mainGui),
          friendsMenuGui_(controller, mainGui),
          messageMenuGui_(controller, mainGui),
          profileManagerGui_(controller, mainGui) {}

    void MainMenuGui::run() {
        setup();

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&stackedWidget_);
        setLayout(layout);

        show();
    }

    void MainMenuGui::on_QuitGameButton_clicked() { actionOnExit(); }

    void MainMenuGui::on_RankingButton_clicked() {
        stackedWidget_.setCurrentWidget(&rankingGui_);
    }

    void MainMenuGui::on_ManageFriendsListButton_clicked() {
        stackedWidget_.setCurrentWidget(&friendsMenuGui_);
    }

    void MainMenuGui::on_MessagesButton_clicked() {
        stackedWidget_.setCurrentWidget(&messageMenuGui_);
    }

    void MainMenuGui::on_CreateGameButton_clicked() {
        gameMenu_.run(true);
        stackedWidget_.setCurrentWidget(&gameMenu_);
    }

    void MainMenuGui::on_JoinGameButton_clicked() {
        gameMenu_.run(false);
        stackedWidget_.setCurrentWidget(&gameMenu_);
    }

    void MainMenuGui::on_ProfileManagerBouton_clicked() {
        stackedWidget_.setCurrentWidget(&profileManagerGui_);
    }

    void MainMenuGui::showMainMenu() {
        stackedWidget_.setCurrentWidget(&mainMenu_);
    }

    /*---------------------------------------------
                    Private Methods
    ----------------------------------------------*/

    void MainMenuGui::actionOnExit() {
        QMessageBox::StandardButton confirmExit;
        confirmExit = QMessageBox::question(
            this, "Quit", "Are you sure you want to quit the game ?",
            QMessageBox::Yes | QMessageBox::No);
        if (confirmExit == QMessageBox::Yes) {
            QApplication::quit();
        }
    }

    void MainMenuGui::setup() {
        QPushButton *createGameButton_ = new QPushButton(this);
        QPushButton *joinGameButton_ = new QPushButton(this);
        QPushButton *messagesButton_ = new QPushButton(this);
        QPushButton *rankingButton_ = new QPushButton(this);
        QPushButton *manageProfileButton_ = new QPushButton(this);
        QPushButton *manageFriendsListButton_ = new QPushButton(this);
        QPushButton *quitGameButton_ = new QPushButton(this);

        createGameButton_->setText("Create a Game");
        createGameButton_->setFixedWidth(500);

        joinGameButton_->setText("Join a Game");
        joinGameButton_->setFixedWidth(500);

        messagesButton_->setText("Messages");
        connect(messagesButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_MessagesButton_clicked);
        messagesButton_->setFixedWidth(500);

        rankingButton_->setText("Ranking");
        connect(rankingButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_RankingButton_clicked);
        rankingButton_->setFixedWidth(500);

        manageProfileButton_->setText("Manage Profile");
        connect(manageProfileButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_ProfileManagerBouton_clicked);
        manageProfileButton_->setFixedWidth(500);

        manageFriendsListButton_->setText("Manage Friends List");
        connect(manageFriendsListButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_ManageFriendsListButton_clicked);
        manageFriendsListButton_->setFixedWidth(500);

        quitGameButton_->setText("Quit Game");
        quitGameButton_->setFixedWidth(500);
        connect(quitGameButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_QuitGameButton_clicked);

        QVBoxLayout *menu = new QVBoxLayout();
        menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                      QSizePolicy::Expanding));
        menu->addWidget(createCenterBoldTitle(
            "Welcome to the main menu of Tetris Royal !"));
        menu->addWidget(createGameButton_, 0, Qt::AlignCenter);
        menu->addWidget(joinGameButton_, 0, Qt::AlignCenter);
        menu->addWidget(messagesButton_, 0, Qt::AlignCenter);
        menu->addWidget(rankingButton_, 0, Qt::AlignCenter);
        menu->addWidget(manageProfileButton_, 0, Qt::AlignCenter);
        menu->addWidget(manageFriendsListButton_, 0, Qt::AlignCenter);
        menu->addWidget(quitGameButton_, 0, Qt::AlignCenter);
        menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                      QSizePolicy::Expanding));

        mainMenu_.setLayout(menu);

        stackedWidget_.addWidget(&mainMenu_);
        stackedWidget_.addWidget(&rankingGui_);
        stackedWidget_.addWidget(&friendsMenuGui_);
        stackedWidget_.addWidget(&messageMenuGui_);
        stackedWidget_.addWidget(&profileManagerGui_);
        stackedWidget_.addWidget(&gameMenu_);

        connect(&rankingGui_, &RankingGui::backToMainMenu, this,
                &MainMenuGui::showMainMenu);
        connect(&friendsMenuGui_, &FriendsMenuGui::backToMainMenu, this,
                &MainMenuGui::showMainMenu);
        connect(&messageMenuGui_, &MessageMenuGui::backToMainMenu, this,
                &MainMenuGui::showMainMenu);
        connect(&profileManagerGui_, &ProfileManagerGui::backToMainMenu, this,
                &MainMenuGui::showMainMenu);
        connect(createGameButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_CreateGameButton_clicked);
        connect(joinGameButton_, &QPushButton::clicked, this,
                &MainMenuGui::on_JoinGameButton_clicked);
        connect(&gameMenu_, &GameMenu::backToMainMenu, this,
                &MainMenuGui::showMainMenu);
    }

} // namespace GUI
