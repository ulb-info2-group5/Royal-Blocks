#include "screen_manager.hpp"

#include "../core/controller/controller.hpp"
#include "GUI/main_gui.hpp"
#include <qapplication.h>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice, std::tuple<int, char **> args)
    : controller_(controller), uiChoice_(uiChoice) {
    if (uiChoice_ == UiChoice::TUI) {
        tui_ = std::make_unique<MainTui>(controller_);
    }
    else {
        int argc = std::get<0>(args);
        char **argv = std::get<1>(args);

        app_ = std::make_unique<QApplication>(argc, argv);
        gui_ = std::make_unique<MainGui>(nullptr, &controller_);
    }
}

void ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_->run();
    }

    else {

        app_->setApplicationName("Royal Tetris");
        app_->setApplicationDisplayName("Royal Tetris");
        gui_->show();
        app_->exec();
    }
}

void ScreenManager::forceRefresh() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_->forceRefresh();
    }
    else {
        gui_->forceRefresh();
    }
}