#include "tetris_window.hpp"

#include "graphics/GUI/login/login.hpp"
#include "main_gui.hpp"
#include "qt_config/qt_config.hpp"

#include <memory>
#include <qmessagebox.h>

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

    void TetrisWindow::showMainMenu() {
        connect(mainMenu_.get(), &MainMenu::quitGame, this, &TetrisWindow::quitGui);

        connect(mainMenu_.get(), &MainMenu::applyDarkTheme, this,
                &TetrisWindow::setDarkMode);
        connect(mainMenu_.get(), &MainMenu::applyLightTheme, this,
                &TetrisWindow::setLightMode);
        mainMenu_->run();
        setCentralWidget(mainMenu_.get());

        login_.reset();
    }

    void TetrisWindow::run() {
        login_ = std::make_unique<Login>(controller_, this);
        mainMenu_ = std::make_unique<MainMenu>(controller_, *this, this);
        
        connect(login_.get(), &Login::loginSuccessful, this,
                &TetrisWindow::showMainMenu);
        login_->run();
        setCentralWidget(login_.get());
    }

    void start() {

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
        
        mainMenu_.reset();
        login_.reset();
        
        run();

        QMessageBox::critical(this, "Disconnected", "You have been disconnected from the server. Please login again or make sure that the server is online.");
    }
    

} // namespace GUI
