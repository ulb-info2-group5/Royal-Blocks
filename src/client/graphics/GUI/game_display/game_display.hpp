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
#include "effect_info.hpp"
#include "graphics/GUI/game_display/effects_selector.hpp"
#include "opponent_widget.hpp"

#include <qgridlayout.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qwidget.h>

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

        QPushButton quitButton_;
        QLCDNumber scoreLCD_;
        QLCDNumber energyLCD_;
        QLabel holdTetromino_;
        EffectInfo bonusInfo_;
        EffectInfo penaltyInfo_;
        EffectSelector effectSelector_;
        QVBoxLayout leftPane_;

        QLabel gameMode_;
        QLabel selfBoard_;
        QLabel tetrominoQueue_;
        QHBoxLayout middlePaneHBox_;
        QVBoxLayout middlePaneLeftVBox_;
        QVBoxLayout middlePane_;

        QGridLayout oppBoards_;
        QVBoxLayout rightPane_;

        // Barre de progression
        QProgressBar progressBar_;

        /**
         * @brief Redraws the board pixmap and returns a pointer to the QLable
         * containing the board pixmap.
         */
        void selfBoard(CellSize size = CellSize::Big);

        void scoreLCD();

        void holdTetromino();

        void energyLCD();

        void tetrominoQueue();

        OpponentWidget *createOppBoard(size_t index, CellSize size);

        void oppBoards();

        void bonusInfo();

        void penaltyInfo();

        void effectsInfo();

        void effectSelector();

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

        void on_EffectBought(EffectType effect);

        void updateGameState();

        // add the functions for the buttons

        // void on_changeTarget_Clicked(size_t index);

        // void refreshScreen();

        // void on_QuitGameButton_clicked();

      protected:
        void keyPressEvent(QKeyEvent *event);

      public:
        GameDisplay(Controller &controller, MainGui &mainGui,
                    QWidget *parent = nullptr);

        ~GameDisplay() = default;

      signals:

        void backToMainMenu();
    };

} // namespace GUI

#endif
