#include "tetris_window.hpp"

#include "graphics/GUI/login/login.hpp"
#include "main_gui.hpp"
#include "qt_config/qt_config.hpp"

#include <QTimer>
#include <QMessageBox>
#include <QStyleFactory>

namespace GUI {

    void TetrisWindow::setDarkMode() {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setPalette(createDarkPalette());
        qApp->setStyleSheet("QToolTip { color: white; background-color: black; "
                            "border: 1px solid white; }");
        QSettings settings("Royal Tetris", "Royal Tetris");
        settings.setValue("theme/darkMode", true);
    }

    void TetrisWindow::setLightMode() {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setPalette(createLightPalette());
        qApp->setStyleSheet("QToolTip { color: black; background-color: white; "
                            "border: 1px solid black; }");
        QSettings settings("Royal Tetris", "Royal Tetris");
        settings.setValue("theme/darkMode", false);
    }

    TetrisWindow::TetrisWindow(Controller &controller, MainGui &mainGui, QWidget *parent) : QMainWindow(parent), controller_(controller) {
        connect(&mainGui, &MainGui::clientDisconnected, this,
                &TetrisWindow::backToLoginMenu);

        QSettings settings("Royal Tetris", "Royal Tetris");
        if (settings.value("theme/darkMode", true).toBool()) {
            setDarkMode();
        } else {
            setLightMode();
        }

        setMinimumSize(600, 500);
        showMaximized();
        setWindowTitle("Tetris Royal");
    }

    void TetrisWindow::forceRefresh(UpdateType updateType) {
        if (updateType == UpdateType::FRIENDS_LIST) {
            QTimer::singleShot(0, this, [this]() {
                emit updateFriendsList();
            });  
        } else if (updateType == UpdateType::FRIEND_REQUESTS) {
            QTimer::singleShot(0, this, [this]() {
                emit updateFriendRequestsList();
            });  
        } else if (updateType == UpdateType::RANKING) {
            QTimer::singleShot(0, this, [this]() {
                emit updateRanking();
            });  
        } else if (updateType == UpdateType::CONVERSATIONS) {
            QTimer::singleShot(0, this, [this]() {
                emit updateConversations();
            });  
        } else if (updateType == UpdateType::GAME_STATE) {
            QTimer::singleShot(0, this, [this]() {
                emit updateGameState();
            });  
        }
    }

    void TetrisWindow::showMainMenu() {
        mainMenu_ = new MainMenu(controller_, *this, this);
        mainMenu_->run();
        setCentralWidget(mainMenu_);

        connect(mainMenu_, &MainMenu::quitGame, this, &TetrisWindow::quitGui);

        connect(mainMenu_, &MainMenu::applyDarkTheme, this,
                &TetrisWindow::setDarkMode);
        connect(mainMenu_, &MainMenu::applyLightTheme, this,
                &TetrisWindow::setLightMode);

        login_->deleteLater();
        login_.clear();
    }

    void TetrisWindow::run() {
        login_ = new Login(controller_, this);
        
        connect(login_, &Login::loginSuccessful, this,
                &TetrisWindow::showMainMenu);

        connect(login_, &Login::quitGame, this, &TetrisWindow::quitGui);
        
        login_->run();
        setCentralWidget(login_);
    }

    void TetrisWindow::quitGui() {
        QMessageBox::StandardButton confirmExit;
        confirmExit = QMessageBox::question(
            this, "Quit", "Are you sure you want to quit the game ?",
            QMessageBox::Yes | QMessageBox::No);
        if (confirmExit == QMessageBox::Yes) {
            QApplication::quit();
        }
    }

    void TetrisWindow::backToLoginMenu() {
        if (login_ && login_->isVisible()) {
            return;
        }
        
        setCentralWidget(nullptr);

        if (mainMenu_) {
            mainMenu_->deleteLater();
            mainMenu_ = nullptr;
        }
        
        if (login_) {
            login_->deleteLater();
            login_ = nullptr;
        }
        
        run();
        QMessageBox::critical(this, "Disconnected", "You have been disconnected from the server. Please login again or make sure that the server is online.");
    }
    

} // namespace GUI
