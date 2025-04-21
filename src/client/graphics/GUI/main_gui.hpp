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
    class MainGui : public AbstractDisplay {
      private:
        QApplication app_;

        TetrisWindow tetrisWindow_;

      public:
        MainGui(int argc, char *argv[]);

        ~MainGui() = default;

        virtual void run(Controller &controller) override;

        virtual void forceRefresh(UpdateType updateType) override;
    };

} // namespace GUI

#endif // MAIN_GUI_HPP
