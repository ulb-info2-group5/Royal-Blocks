#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "graphics/GUI/tetris_window.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QStyleFactory>
#include <QTableWidget>
#include <qapplication.h>

namespace GUI {

    MainGui::MainGui(int argc, char *argv[])
        : app_(argc, argv), tetrisWindow_() {
        app_.setApplicationName("Royal Tetris");
        app_.setApplicationDisplayName("Royal Tetris");
    }

    void MainGui::run(Controller &controller) {
        tetrisWindow_.run(controller);
        app_.exec();
    }

    void MainGui::forceRefresh(UpdateType updateType) {
        tetrisWindow_.forceRefresh(updateType);
    }

} // namespace GUI
