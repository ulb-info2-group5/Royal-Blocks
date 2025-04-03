// #include "game_display_gui.hpp"
// #include "../qt_config/qt_config.hpp"

// #include "board/board.hpp"
// #include "core/in_game/effects/timed_bonus.hpp"
// #include "core/in_game/game_state/game_state.hpp"
// #include "core/in_game/game_state/game_state_viewer.hpp"
// #include "effect/effect_type.hpp"
// #include "effect_price/effect_price.hpp"
// #include "game_mode/game_mode.hpp"

// #include "graphics/common/abstract_game_display.hpp"
// #include "../../../core/controller/controller.hpp"
// #include "../main_tui.hpp"
// #include "player_state/player_state.hpp"
// #include "tetromino/tetromino.hpp"
// #include "vec2/vec2.hpp"

// #include <memory>
// #include <optional>
// #include <stdexcept>
// #include <string>
// #include <type_traits>
// #include <utility>
// #include <variant>
// #include <vector>

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

// QColor getQColor(AbstractGameDisplay::Color col, selfCellType selfCellType) {

//     QColor returnValue = QColor::fromRgb(0,0,255);

//     switch (col) {
//         case AbstractGameDisplay::Color::Black:
//             returnValue = QColor::fromRgb(0,0,0);
//             break;
//         case AbstractGameDisplay::Color::White:
//             returnValue = QColor::fromRgb(255,255,255);
//             break;
//         case AbstractGameDisplay::Color::Grey:
//             returnValue = QColor::fromRgb(160,160,160);
//             break;
//         case AbstractGameDisplay::Color::DarkBlue:
//             returnValue = QColor::fromRgb(0,0,153);
//             break;
//         case AbstractGameDisplay::Color::LightBlue:
//             returnValue = QColor::fromRgb(51,255,255);
//             break;
//         case AbstractGameDisplay::Color::Purple:
//             returnValue = ftQColor::fromRgb(153,0,153);
//             break;
//         case AbstractGameDisplay::Color::Red:
//             returnValue = QColor::fromRgb(255,0,0);
//             break;
//         case AbstractGameDisplay::Color::Orange:
//             returnValue = QColor::fromRgb(255,153,51);
//             break;
//         case AbstractGameDisplay::Color::Pink:
//             returnValue = QColor::fromRgb(255,102,178);
//             break;
//         case AbstractGameDisplay::Color::Green:
//             returnValue = QColor::fromRgb(128,155,0);
//             break;
//         case AbstractGameDisplay::Color::Yellow:
//             returnValue = QColor::fromRgb(255,255,0);
//             break;
//         };
    
//         if (selfCellType == SelfCellType::Preview) {
//             returnValue = QColor::fromRgb(128,128,128,200);
//         }
    
//         return returnValue;
// }

// GameDisplayGUI::GameDisplayGUI(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr) :
//     AbstractGameDisplay(controller), mainGui_(mainGui), QWidget(parent) {}

// // private methods 

// //void GameDisplayGUI::quitButton();

// void GameDisplayGUI::playerInfo();

// void GameDisplayGUI::energy();

// //void GameDisplayGUI::availableEffects();

// void GameDisplayGUI::penaltyInfo();

// void GameDisplayGUI::bonusInfo();

// void GameDisplayGUI::holdTetromino();

// void GameDisplayGUI::leftPane();

// void GameDisplayGUI::drawBoard(CellSize size = CellSize::Big, Qimage &board);

// void GameDisplayGUI::tetrominoQueue();

// void GameDisplayGUI::middlePane();

// void GameDisplayGUI::opponentsBoard();

// void GameDisplayGUI::rightPane();

// void GameDisplayGUI::drawEndlessMode();

// void GameDisplayGUI::drawMultiMode();

// void GameDisplayGUI::drawGameOver();

// void GameDisplayGUI::drawWin();

// void GameDisplayGUI::drawSpectate();

// void GameDisplayGUI::handleKeys();

// void GameDisplayGUI::updateScreen();

// void GameDisplayGUI::setup() {
//     QPushButton *quitButton_ = new QPushButton(this);
        
//     if (getGameMode() == GameMode::RoyalCompetition || 
//     getGameMode() == GameMode::Classic){
//         for (int i = 0; i < getNumOpponents(); i++){
//             QPushButton *targetButton = new QPushButton(this);
//             targetButtons_.push_back(targetButton);
//         }
//     }

//     //if (getGameMode() == GameMode::RoyalCompetition) {} effects lol
// }

// // private slots 

// void GameDisplayGUI::changeTarget(unsigned targetIdx = 0);

// void GameDisplayGUI::refreshScreen();

// // signals

// void GameDisplayGUI::quitGame();
