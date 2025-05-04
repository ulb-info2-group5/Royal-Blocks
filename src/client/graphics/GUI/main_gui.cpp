#include "main_gui.hpp"

#include "graphics/GUI/tetris_window.hpp"
#include "graphics/common/abstract_display.hpp"


namespace GUI {

    MainGui::MainGui(Controller &controller, int argc, char *argv[])
        : AbstractDisplay(controller), app_(argc, argv), tetrisWindow_(controller, *this) {
        app_.setApplicationName("Royal Tetris");
        app_.setApplicationDisplayName("Royal Tetris");
    }

    void MainGui::run() {
        tetrisWindow_.run();
        app_.exec();
    }

    void MainGui::forceRefresh(UpdateType updateType) {
        tetrisWindow_.forceRefresh(updateType);
    }

    void MainGui::onDisconnected() {
        emit clientDisconnected();
    }

} // namespace GUI
