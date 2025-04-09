// #include "game_display.hpp"
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

// namespace GUI {

//     constexpr int QUITGAME_BUTTON_WIDTH = 150;
//     constexpr int OP_BUTTON_WIDTH = 25;
//     constexpr int MODE_LABEL_WIDTH = 150;
//     constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 10,
//                      HEIGHT_CANVAS_BIG =
//                          static_cast<size_t>(CellSize::Big) * 20,
//                      WIDTH_CANVAS_SMALL =
//                          static_cast<size_t>(CellSize::Small) * 10,
//                      HEIGHT_CANVAS_SMALL =
//                          static_cast<size_t>(CellSize::Small) * 20;


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

// GameDisplay::GameDisplay(Controller &controller, MainGui &mainGui,
// QWidget *parent = nullptr) :
//     AbstractGameDisplay(controller), mainGui_(mainGui), QWidget(parent) {}

// // private methods

// //void GameDisplay::quitButton();

// void GameDisplay::playerInfo();

// void GameDisplay::energy();

// //void GameDisplay::availableEffects();

// void GameDisplay::penaltyInfo();

// void GameDisplay::bonusInfo();

// void GameDisplay::holdTetromino();

// void GameDisplay::leftPane();

// QImage GameDisplay::drawBoard(CellSize size = CellSize::Big) {

//     size_t height = getBoardHeight();
//     size_t width = getBoardWidth();
//     size_t cellSize = static_cast<size_t>(size);

//     // maybe not working because this format only works with color palette
//     QImage selfBoard(cellSize * width, cellSize * height, QImage::Format_ARGB32);

//     for (uint32_t y = 0; y < height; ++y) {
//         for (uint32_t x = 0; x < width; ++x) {
//             QColor color = selfCellInfoAt(x,y)
//                 .transform([](auto cellInfo) {
//                 return getQColor(colorIdToColor(cellInfo.first), cellInfo.second);
//             })
//                 .value_or(getQColor(Color::Black));

//             for (uint32_t dy = 0; dy < cellSize; ++dy) {
//                 for (uint32_t dx = 0; dx < cellSize; ++dx) {
//                     selfCanvas.setPixelColor(
//                         x * cellSize + dx, 
//                         (height - 1 - y) * cellSize + dy,
//                         color);
//                 }
//             }
//         }
//     }

//     return selfBoard;
// }

// void GameDisplay::tetrominoQueue();

// void GameDisplay::middlePane();

// void GameDisplay::opponentsBoard();

// void GameDisplay::rightPane();

// void GameDisplay::drawEndlessMode();

// void GameDisplay::drawMultiMode();

//void GameDisplay::drawGameOver(){

    // Creat new space
    // The layout is directly charged
//    QVBoxLayout *layout = new QVBoxLayout(this);

    // Creat label for the text
//    QLabel *label = new QLabel("Game Over");

    // Choose the police
//    QFont font("Arial", 30, QFont::Bold); // Police Arial, taille 50, gras
//    label->setFont(font);

    // Center the text
//    label->setAlignment(Qt::AlignCenter);

    // Add the QLabel to the layout
//    layout->addWidget(label);
//};

// void GameDisplay::drawWin(){
        // Creat new space
    // The layout is directly charged
//    QVBoxLayout *layout = new QVBoxLayout(this);

    // Creat label for the text
//    QLabel *label = new QLabel("The game is won");

    // Choose the police
//    QFont font("Arial", 30, QFont::Bold); // Police Arial, taille 50, gras
//    label->setFont(font);

    // Center the text
//    label->setAlignment(Qt::AlignCenter);

    // Add the QLabel to the layout
//    layout->addWidget(label);
//};

// void GameDisplay::drawSpectate();

// void GameDisplay::handleKeys();

// void GameDisplay::updateScreen();

// void GameDisplay::setup() {
//     QPushButton *quitButton_ = new QPushButton(this);
//     quitButton_->setText("Quit Game");
//     quitButton_->setFixedWidth(QUITGAME_BUTTON_WIDTH);
//     connect(quitButton_, &QPushButton::clicked, this, &GameDisplay::on_QuitGameButton_clicked);


//     if (getGameMode() == GameMode::RoyalCompetition ||
//     getGameMode() == GameMode::Classic){
//         //verify the linkage
//         for (int i = 0; i < getNumOpponents(); i++){
//             QPushButton *targetButton = new QPushButton(this);
//             targetButton->setText(getOpponentUsername(i));
//             connect(targetButton, &QPushButton::clicked, [i, this]() {
//                on_changeTarget_Clicked(i); 
//             })
//             targetButtons_.push_back(targetButton);
//         }
//     }

//     mode_->setText(to_string(getGameMode()));
//     mode_->setFixedWidth(MODE_LABEL_WIDTH);

//     //if (getGameMode() == GameMode::RoyalCompetition) {} effects lol
// }

// // private slots

// void GameDisplay::on_changeTarget_Clicked(size_t index) {
//     controller_.selectTarget(getNthOpponentUserID(index));

//     // if (getSelectedTarget() == getNthOpponentUserID(index)) {
//     //     targetButtons_.at(index).set
//     // }
// }

// void GameDisplay::on_QuitGameButton_clicked() {
//     controller_.quitGame();
//     mainGui_.stopRender();
// }

// void GameDisplay::refreshScreen();

// // signals

// void GameDisplay::quitGame();

// }
