#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "graphics/GUI/qt_config/qt_config.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QStyleFactory>
#include <QTableWidget>

namespace GUI {

    MainGui::MainGui(QWidget *parent) : QMainWindow(parent) {

        QSettings settings("Royal Tetris", "Royal Tetris");
        if (settings.value("theme/darkMode", true).toBool()) {
            setDarkMode();
        } else {
            setLightMode();
        }

        setMinimumSize(600, 500);
        showMaximized();
        setWindowTitle("Tetris Royal");

        show();
    }

    void MainGui::run(Controller &controller) {
        login_ = new Login(controller);
        login_->run();

        mainMenu_ = new MainMenu(controller, *this);

        this->setCentralWidget(login_);
        connect(login_, &Login::loginSuccessful, this, &MainGui::showMainMenu);
    }

    void MainGui::forceRefresh(UpdateType updateType) {
        if (updateType == UpdateType::FRIENDS_LIST) {
            emit updateFriendsList();
        } else if (updateType == UpdateType::FRIEND_REQUESTS) {
            emit updateFriendRequestsList();
        } else if (updateType == UpdateType::RANKING) {
            emit updateRanking();
        } else if (updateType == UpdateType::CONVERSATIONS) {
            emit updateConversations();
        } else if (updateType == UpdateType::GAME_STATE) {
            emit updateGameState();
        }
    }

    void MainGui::showMainMenu() {
        if (login_) {
            login_->deleteLater(); // Delete login because we don't need it
                                   // anymore
        }
        mainMenu_->run();
        this->setCentralWidget(mainMenu_);
        connect(mainMenu_, &MainMenu::quitGame, this, &MainGui::quitGui);

        connect(mainMenu_, &MainMenu::applyDarkTheme, this,
                &MainGui::setDarkMode);
        connect(mainMenu_, &MainMenu::applyLightTheme, this,
                &MainGui::setLightMode);
    }

    void MainGui::quitGui() {
        QMessageBox::StandardButton confirmExit;
        confirmExit = QMessageBox::question(
            this, "Quit", "Are you sure you want to quit the game ?",
            QMessageBox::Yes | QMessageBox::No);
        if (confirmExit == QMessageBox::Yes) {
            QApplication::quit();
        }
    }

    void MainGui::setDarkMode() {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setPalette(createDarkPalette());
        qApp->setStyleSheet("QToolTip { color: white; background-color: black; "
                            "border: 1px solid white; }");
        QSettings settings("Royal Tetris", "Royal Tetris");
        settings.setValue("theme/darkMode", true);
    }

    void MainGui::setLightMode() {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setPalette(createLightPalette());
        qApp->setStyleSheet("QToolTip { color: black; background-color: white; "
                            "border: 1px solid black; }");
        QSettings settings("Royal Tetris", "Royal Tetris");
        settings.setValue("theme/darkMode", false);
    }

} // namespace GUI
