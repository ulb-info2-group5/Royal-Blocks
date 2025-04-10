#ifndef GUI_GAME_DISPLAY_HPP
#define GUI_GAME_DISPLAY_HPP

#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../../common/abstract_game_display.hpp"

#include "../../../../common/types/types.hpp"

#include <qlabel.h>
#include <qpixmap.h>

class Controller;

namespace GUI {

    class MainGui;

    enum class CellSize : size_t {
        Small = 10,
        Big = 40,
    };

    class GameDisplay final : public QWidget, public AbstractGameDisplay {

        Q_OBJECT

      private:
        MainGui &mainGui_;

        QHBoxLayout mainLayout_;

        QLCDNumber scoreLCD_;
        QVBoxLayout leftPane_;

        QLabel selfBoard_;
        QVBoxLayout middlePane_;

        QVBoxLayout rightPane_;

        /**
         * @brief Redraws the board pixmap and returns a pointer to the QLable
         * containing the board pixmap.
         */
        void selfBoard(CellSize size = CellSize::Big);

        void scoreLCD();

        // QGridLayout opLayout_;
        // QLabel playerInfo_;
        // QProgressBar penalty_;
        // QImage holdTetromino_;

        // std::vector<QPushButton> effectsButtons_;
        // QVBoxLayout effectsLayout_;
        // QProgressBar energy_;
        // QProgressBar bonus_;

        // QImage selfBoard_;
        // QLabel mode_;
        // QImage tetrominoQueue_;

        // std::vector<QImage> opBoards_;
        // std::vector<QPushButton> targetButtons_;
        // std::vector<QVBoxLayout> opSingularDisplay_;

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

        void on_QuitButtonClicked();

        void updateGameState();

        // add the functions for the buttons

        // void on_changeTarget_Clicked(size_t index);

        // void refreshScreen();

        // void on_QuitGameButton_clicked();

      public:
        GameDisplay(Controller &controller, MainGui &mainGui,
                    QWidget *parent = nullptr);

        ~GameDisplay() = default;

      signals:

        void backToMainMenu();
    };

} // namespace GUI

#endif
