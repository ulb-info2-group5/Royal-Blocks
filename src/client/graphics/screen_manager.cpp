#include "screen_manager.hpp"

#include <qapplication.h>

#include "GUI/mainwindow.h"
#include "../core/controller/controller.hpp"

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice)
    : controller_(controller), uiChoice_(uiChoice), tui_(controller) {}

void ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        MainTui tui(controller_);
        tui.run();
    }

    else {
        int argc = 2;
        char *argv[] = {"./tetris_royal_client", "--gui"};
        QApplication app(argc, argv);
        MainWindow mainWindow(nullptr, &controller_);
        mainWindow.show();
        app.exec();
    }
}

void ScreenManager::forceRefresh() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_.forceRefresh();
    }
    else {
        //TODO: refresh to GUI
    }
}