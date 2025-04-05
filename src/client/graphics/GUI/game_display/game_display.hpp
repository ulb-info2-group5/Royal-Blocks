// #ifndef GUI_GAME_DISPLAY_HPP
// #define GUI_GAME_DISPLAY_HPP

// #include <QWidget>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QGridLayout>
// #include <QPushButton>
// #include <QLineEdit>
// #include <QLabel>
// #include <QImage>
// #include <QColor>
// #include <QProgressBar>

// #include "../../common/abstract_game_display.hpp"

// #include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
// #include "../../../../common/types/types.hpp"
// #include "../../../core/in_game/game_state/game_state.hpp"
// #include "../../../core/in_game/game_state/game_state_viewer.hpp"

// #include <memory>
// #include <variant>
// #include <vector>

// class Controller;

// class MainGui;

// enum class CellSize : size_t {
//     Small = 4,
//     Big = 8,
// };

// constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 10,
//                  HEIGHT_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 20,
//                  WIDTH_CANVAS_SMALL = static_cast<size_t>(CellSize::Small) *
//                  10, HEIGHT_CANVAS_SMALL =
//                      static_cast<size_t>(CellSize::Small) * 20;

// class GameDisplayGUI final : public QWidget, public AbstractGameDisplay {

//     Q_OBJECT

//     private:

//     Controller &controller_;
//     MainGui &mainGui_;

//     QWidget *mainWidget_;
//     QHBoxLayout mainLayout_;
//     QVBoxLayout leftPane_;
//     QVBoxLayout middlePane_;
//     QGridLayout opLayout_;

//     QPushButton quitButton_;
//     QLabel playerInfo_;
//     //std::vector<QPushButton> effectsButtons_;
//     //QVBoxLayout effectsLayout_;
//     QProgressBar energy_;
//     QProgressBar penalty_;
//     QProgressBar bonus_;
//     QImage holdTetromino_;

//     QImage selfBoard_;
//     QLabel mode_;
//     QImage tetrominoQueue_;

//     std::vector<QImage> opBoards_;
//     std::vector<QPushButton> targetButtons_;

//     //void quitButton();
//     void playerInfo();
//     void energy();
//     //void availableEffects();
//     void penaltyInfo();
//     void bonusInfo();
//     void holdTetromino();
//     void leftPane();

//     void drawBoard(QImage &board, CellSize size = CellSize::Big);
//     void tetrominoQueue();
//     void middlePane();

//     void opponentsBoard();

//     void rightPane();

//     void drawEndlessMode();
//     void drawMultiMode();

//     void drawGameOver();
//     void drawWin();
//     void drawSpectate();

//     void handleKeys();

//     void updateScreen();

//     void setup();

// private slots:

//         // add the functions for the buttons

//         void changeTarget(unsigned int targetIdx);

//         void refreshScreen();

//     public:

//         GameDisplayGUI(Controller &controller, MainGui &mainGui, QWidget
//         *parent = nullptr);

//         ~GameDisplayGUI() = default;

//     signals:

//         void quitGame();

// };

// #endif
