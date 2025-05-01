#ifndef GUI_MAIN_GUI_HPP
#define GUI_MAIN_GUI_HPP

#include "../common/abstract_display.hpp"
#include "tetris_window.hpp"

#include <QApplication>
#include <qobjectdefs.h>

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
