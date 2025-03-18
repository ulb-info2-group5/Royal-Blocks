#include "screen_manager.hpp"

#include "../core/controller/controller.hpp"
#include "GUI/main_gui.hpp"
#include <qapplication.h>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice)
    : controller_(controller), uiChoice_(uiChoice), tui_(controller) {}

void ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_.run();
    }

    else {
        int argc = 2;
        char *argv[] = {"./tetris_royal_client", "--gui"};
        QApplication app(argc, argv);
        MainGui mainGui(nullptr, &controller_);
        mainGui.show();
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