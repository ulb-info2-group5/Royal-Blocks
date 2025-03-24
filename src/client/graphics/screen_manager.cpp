#include "screen_manager.hpp"

#include "../core/controller/controller.hpp"
#include "GUI/main_gui.hpp"
#include <qapplication.h>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice, std::tuple<int, char **> args)
    : controller_(controller), uiChoice_(uiChoice), args_(args), tui_(controller) {}

void ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_.run();
    }

    else {
        int argc = std::get<0>(args_);
        char **argv = std::get<1>(args_);
        
        QApplication app(argc, argv);
        MainGui mainGui(nullptr, &controller_);
        app.setApplicationName("Tetris Royal");
        app.setApplicationDisplayName("Tetris Royal");
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