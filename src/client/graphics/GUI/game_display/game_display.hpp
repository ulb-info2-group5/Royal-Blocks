#ifndef GUI_GAME_DISPLAY_HPP
#define GUI_GAME_DISPLAY_HPP

#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../../common/abstract_game_display.hpp"

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"
#include "../../../core/in_game/game_state/game_state.hpp"
#include "../../../core/in_game/game_state/game_state_viewer.hpp"

#include <memory>
#include <variant>
#include <vector>

class Controller;

namespace GUI {

    class MainGui;

    enum class CellSize : size_t {
        Small = 4,
        Big = 8,
    };

    // constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) *
    // 10,
    //                  HEIGHT_CANVAS_BIG = static_cast<size_t>(CellSize::Big) *
    //                  20, WIDTH_CANVAS_SMALL =
    //                  static_cast<size_t>(CellSize::Small) * 10,
    //                  HEIGHT_CANVAS_SMALL =
    //                      static_cast<size_t>(CellSize::Small) * 20;

    class GameDisplay final : public QWidget, public AbstractGameDisplay {

        Q_OBJECT

      private:
        MainGui &mainGui_;

        QWidget *mainWidget_;
        QHBoxLayout mainLayout_;
        QVBoxLayout leftPane_;
        QVBoxLayout middlePane_;
        QGridLayout opLayout_;

        QPushButton *quitButton_;
        QLabel playerInfo_;
        QProgressBar penalty_;
        QImage holdTetromino_;

        // std::vector<QPushButton> effectsButtons_;
        // QVBoxLayout effectsLayout_;
        QProgressBar energy_;
        QProgressBar bonus_;

        QImage selfBoard_;
        QLabel mode_;
        QImage tetrominoQueue_;

        std::vector<QImage> opBoards_;
        std::vector<QPushButton> targetButtons_;
        std::vector<QVBoxLayout> opSingularDisplay_;

        // void playerInfo();
        // void penaltyInfo();
        // void bonusInfo();
        // void energy();
        // void availableEffects();
        // void holdTetromino();
        // void leftPane();

        // void drawBoard(CellSize size = CellSize::Big);
        // void tetrominoQueue();
        // void middlePane();

        // void createOpBoardDisplay(size_t index, CellSize size);
        // void opponentsBoard();
        // void rightPane();

        // void drawMainLayout();

        // void drawGameOver();
        // void drawWin();

        // void handleKeys();

        // void updateScreen();

        void setup();

        // void actionOnExit();

        // void changeTarget();

      private slots:

        // add the functions for the buttons

        // void on_changeTarget_Clicked(size_t index);

        // void refreshScreen();

        // void on_QuitGameButton_clicked();

      public:
        GameDisplay(Controller &controller, MainGui &mainGui,
                    QWidget *parent = nullptr);

        ~GameDisplay() = default;

      signals:

        void quitGame();
    };

} // namespace GUI

#endif
