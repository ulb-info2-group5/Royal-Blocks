#include "main_menu.hpp"

#include "../friends_menu/friends_menu.hpp"
#include "../game_menu/game_menu.hpp"
#include "../main_gui.hpp"
#include "../message_menu/message_menu.hpp"
#include "../profile_manager/profile_manager.hpp"
#include "../qt_config/qt_config.hpp"
#include "graphics/GUI/game_display/game_display.hpp"
#include "../theme_manager/theme_manager.hpp"

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
          profileManager_(controller, mainGui), themeManager_(this) {}

    void MainMenu::run() {
        setup();

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&stackedWidget_);
        this->setLayout(layout);

        this->show();
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

    void MainMenu::on_ThemeManagerButton_clicked() {
        stackedWidget_.setCurrentWidget(&themeManager_);
    }

    void MainMenu::showMainMenu() {
        stackedWidget_.setCurrentWidget(&mainMenu_);
    }

    /*---------------------------------------------
                    Private Methods
    ----------------------------------------------*/
    void MainMenu::setup() {
        QPushButton *createGameButton = new QPushButton(this);
        createGameButton->setAutoDefault(true);
        QPushButton *joinGameButton = new QPushButton(this);
        joinGameButton->setAutoDefault(true);
        QPushButton *messagesButton = new QPushButton(this);
        messagesButton->setAutoDefault(true);
        QPushButton *rankingButton = new QPushButton(this);
        rankingButton->setAutoDefault(true);
        QPushButton *manageProfileButton = new QPushButton(this);
        manageProfileButton->setAutoDefault(true);
        QPushButton *manageFriendsListButton = new QPushButton(this);
        manageFriendsListButton->setAutoDefault(true);
        QPushButton *quitGameButton = new QPushButton(this);
        quitGameButton->setAutoDefault(true);
        QPushButton *themeButton = new QPushButton(this);
        themeButton->setAutoDefault(true);

        createGameButton->setText("Create a Game");
        createGameButton->setFixedWidth(500);

        joinGameButton->setText("Join a Game");
        joinGameButton->setFixedWidth(500);

        messagesButton->setText("Messages");
        connect(messagesButton, &QPushButton::clicked, this,
                &MainMenu::on_MessagesButton_clicked);
        messagesButton->setFixedWidth(500);

        rankingButton->setText("Ranking");
        connect(rankingButton, &QPushButton::clicked, this,
                &MainMenu::on_RankingButton_clicked);
        rankingButton->setFixedWidth(500);

        manageProfileButton->setText("Manage Profile");
        connect(manageProfileButton, &QPushButton::clicked, this,
                &MainMenu::on_ProfileManagerBouton_clicked);
        manageProfileButton->setFixedWidth(500);

        manageFriendsListButton->setText("Manage Friends List");
        connect(manageFriendsListButton, &QPushButton::clicked, this,
                &MainMenu::on_ManageFriendsListButton_clicked);
        manageFriendsListButton->setFixedWidth(500);

        themeButton->setText("Change Theme");
        connect(themeButton, &QPushButton::clicked, this,
                &MainMenu::on_ThemeManagerButton_clicked);
        themeButton->setFixedWidth(500);

        quitGameButton->setText("Quit Game");
        quitGameButton->setFixedWidth(500);
        connect(quitGameButton, &QPushButton::clicked, this,
                &MainMenu::on_QuitGameButton_clicked);

        QVBoxLayout *menu = new QVBoxLayout();
        menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                      QSizePolicy::Expanding));
        menu->addWidget(createCenterBoldTitle(
            "Welcome to the main menu of Tetris Royal !"));
        menu->addWidget(createGameButton, 0, Qt::AlignCenter);
        menu->addWidget(joinGameButton, 0, Qt::AlignCenter);
        menu->addWidget(messagesButton, 0, Qt::AlignCenter);
        menu->addWidget(rankingButton, 0, Qt::AlignCenter);
        menu->addWidget(manageProfileButton, 0, Qt::AlignCenter);
        menu->addWidget(manageFriendsListButton, 0, Qt::AlignCenter);
        menu->addWidget(themeButton, 0, Qt::AlignCenter);
        menu->addWidget(quitGameButton, 0, Qt::AlignCenter);
        menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                      QSizePolicy::Expanding));

        mainMenu_.setLayout(menu);

        stackedWidget_.addWidget(&mainMenu_);
        stackedWidget_.addWidget(&ranking_);
        stackedWidget_.addWidget(&friendsMenu_);
        stackedWidget_.addWidget(&messageMenu_);
        stackedWidget_.addWidget(&profileManager_);
        stackedWidget_.addWidget(&themeManager_);
        stackedWidget_.addWidget(&gameMenu_);

        connect(&ranking_, &Ranking::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&friendsMenu_, &FriendsMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&messageMenu_, &MessageMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&profileManager_, &ProfileManager::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(createGameButton, &QPushButton::clicked, this,
                &MainMenu::on_CreateGameButton_clicked);
        connect(joinGameButton, &QPushButton::clicked, this,
                &MainMenu::on_JoinGameButton_clicked);
        connect(&gameMenu_, &GameMenu::backToMainMenu, this,
                &MainMenu::showMainMenu);
        connect(&themeManager_, &ThemeManager::backToMainMenu, this,
                &MainMenu::showMainMenu);

        connect(&themeManager_, &ThemeManager::applyLightTheme, this,
                [this] {emit applyLightTheme(); });
        connect(&themeManager_, &ThemeManager::applyDarkTheme, this,
                [this] {emit applyDarkTheme(); });
    }

} // namespace GUI
