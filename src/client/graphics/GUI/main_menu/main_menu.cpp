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
#include <qobjectdefs.h>

namespace GUI {

    MainMenu::MainMenu(Controller &controller, MainGui &mainGui,
                       QWidget *parent)
        : QWidget(parent), controller_(controller),
          ranking_(controller_, mainGui), gameMenu_(controller, mainGui),
          friendsMenu_(controller, mainGui), messageMenu_(controller, mainGui),
          profileManager_(controller, mainGui) {}

    void MainMenu::run() {
        setup();

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&stackedWidget_);
        setLayout(layout);

        show();
    }

    void MainMenu::on_QuitGameButton_clicked() { 
        emit quitGame();
     }

    void MainMenu::on_RankingButton_clicked() {
        stackedWidget_.setCurrentWidget(&ranking_);
    }

    void MainMenu::on_ManageFriendsListButton_clicked() {
        stackedWidget_.setCurrentWidget(&friendsMenu_);
    }

    void MainMenu::on_MessagesButton_clicked() {
        stackedWidget_.setCurrentWidget(&messageMenu_);
    }

    void MainMenu::on_CreateGameButton_clicked() {
        gameMenu_.run(true);
        stackedWidget_.setCurrentWidget(&gameMenu_);
    }

    void MainMenu::on_JoinGameButton_clicked() {
        gameMenu_.run(false);
        stackedWidget_.setCurrentWidget(&gameMenu_);
    }

    void MainMenu::on_ProfileManagerBouton_clicked() {
        stackedWidget_.setCurrentWidget(&profileManager_);
    }

    void MainMenu::showMainMenu() {
        stackedWidget_.setCurrentWidget(&mainMenu_);
    }

    /*---------------------------------------------
                    Private Methods
    ----------------------------------------------*/
    void MainMenu::setup() {
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
                &MainMenu::on_MessagesButton_clicked);
        messagesButton_->setFixedWidth(500);

        rankingButton_->setText("Ranking");
        connect(rankingButton_, &QPushButton::clicked, this,
                &MainMenu::on_RankingButton_clicked);
        rankingButton_->setFixedWidth(500);

        manageProfileButton_->setText("Manage Profile");
        connect(manageProfileButton_, &QPushButton::clicked, this,
                &MainMenu::on_ProfileManagerBouton_clicked);
        manageProfileButton_->setFixedWidth(500);

        manageFriendsListButton_->setText("Manage Friends List");
        connect(manageFriendsListButton_, &QPushButton::clicked, this,
                &MainMenu::on_ManageFriendsListButton_clicked);
        manageFriendsListButton_->setFixedWidth(500);

        quitGameButton_->setText("Quit Game");
        quitGameButton_->setFixedWidth(500);
        connect(quitGameButton_, &QPushButton::clicked, this,
                &MainMenu::on_QuitGameButton_clicked);

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
        stackedWidget_.addWidget(&ranking_);
        stackedWidget_.addWidget(&friendsMenu_);
        stackedWidget_.addWidget(&messageMenu_);
        stackedWidget_.addWidget(&profileManager_);
        stackedWidget_.addWidget(&gameMenu_);

        connect(&ranking_, &Ranking::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&friendsMenu_, &FriendsMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&messageMenu_, &MessageMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&profileManager_, &ProfileManager::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(createGameButton_, &QPushButton::clicked, this,
                &MainMenu::on_CreateGameButton_clicked);
        connect(joinGameButton_, &QPushButton::clicked, this,
                &MainMenu::on_JoinGameButton_clicked);
        connect(&gameMenu_, &GameMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
    }

} // namespace GUI
