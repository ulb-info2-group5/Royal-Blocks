#include "graphics/GUI/tetris_window.hpp"

#include "qt_config/qt_config.hpp"

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

    TetrisWindow::TetrisWindow(QWidget *parent) : QMainWindow(parent) {
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
        if (login_) {
            login_->deleteLater(); // Delete login because we don't need it
                                   // anymore
        }
        mainMenu_->run();
        this->setCentralWidget(mainMenu_);
        connect(mainMenu_, &MainMenu::quitGame, this, &TetrisWindow::quitGui);

        connect(mainMenu_, &MainMenu::applyDarkTheme, this,
                &TetrisWindow::setDarkMode);
        connect(mainMenu_, &MainMenu::applyLightTheme, this,
                &TetrisWindow::setLightMode);
    }

    void TetrisWindow::run(Controller &controller) {
        login_ = new Login(controller);
        login_->run();

        mainMenu_ = new MainMenu(controller, *this);

        this->setCentralWidget(login_);
        connect(login_, &Login::loginSuccessful, this,
                &TetrisWindow::showMainMenu);
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

} // namespace GUI
