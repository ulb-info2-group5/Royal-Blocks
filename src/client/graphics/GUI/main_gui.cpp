/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main_gui.hpp"

#include "graphics/GUI/tetris_window.hpp"
#include "graphics/common/abstract_display.hpp"

#include <QTimer>

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
        QTimer::singleShot(0, this, [this]() {
            emit clientDisconnected();
        });  
    }

} // namespace GUI
