#include "screen_manager.hpp"

#include "../core/controller/controller.hpp"
#include "GUI/main_gui.hpp"
#include <qapplication.h>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice,
                             std::pair<int, char **> args)
    : controller_(controller), uiChoice_(uiChoice) {
    if (uiChoice_ == UiChoice::TUI) {
        tui_ = std::make_unique<TUI::MainTui>(controller_);
    } else {
        auto [argc, argv] = args;
        app_ = std::make_unique<QApplication>(argc, argv);
        gui_ = std::make_unique<GUI::MainGui>(controller_);
    }
}

int ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        tui_->run();
        return 0;
    }

    app_->setApplicationName("Royal Tetris");
    app_->setApplicationDisplayName("Royal Tetris");
    gui_->run();
    gui_->show();
    return app_->exec();
}

void ScreenManager::forceRefresh(UpdateType updateType) {
    if (uiChoice_ == UiChoice::TUI) {
        tui_->forceRefresh();
    } else {
        if (updateType != UpdateType::OTHER) {
            gui_->forceRefresh(updateType);
        }
    }
}
