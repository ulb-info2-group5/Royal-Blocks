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

#ifndef GUI_MAIN_GUI_HPP
#define GUI_MAIN_GUI_HPP

#include "../common/abstract_display.hpp"
#include "tetris_window.hpp"

#include <QApplication>

class Controller;

namespace GUI {

    /**
     * @brief Manages the GUI component of the program.
     * Owns and manages the QApplication and the Mainwindow of the GUI tetris
     * client.
     */
    class MainGui final : public QObject, public AbstractDisplay {
        Q_OBJECT

      private:
        QApplication app_;

        TetrisWindow tetrisWindow_;

      public:
        MainGui(Controller &controller, int argc, char *argv[]);

        ~MainGui() = default;

        void run() override;

        void forceRefresh(UpdateType updateType) override;

        void onDisconnected() override;

      signals:
        /**
         * @brief Signal emitted when the client is disconnected from the server.
         */
        void clientDisconnected();
    };

} // namespace GUI

#endif // MAIN_GUI_HPP
