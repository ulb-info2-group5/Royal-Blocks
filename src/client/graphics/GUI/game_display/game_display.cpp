#include "game_display.hpp"
#include "../qt_config/qt_config.hpp"

#include "board/board.hpp"
#include "core/in_game/effects/timed_bonus.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"
#include "effect/effect_type.hpp"
#include "effect_price/effect_price.hpp"
#include "game_mode/game_mode.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "graphics/common/abstract_game_display.hpp"
#include "player_state/player_state.hpp"
#include "tetromino/tetromino.hpp"
#include "vec2/vec2.hpp"

#include <QColor>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <qchar.h>
#include <qcolor.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <stdexcept>
#include <string>

namespace GUI {

    // constexpr int QUITGAME_BUTTON_WIDTH = 150;
    // constexpr int OP_BUTTON_WIDTH = 25;
    // constexpr int MODE_LABEL_WIDTH = 150;
    // constexpr int PLAYER_INFO_LABEL_WIDTH = 150;
    // constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) *
    // 10,
    //                  HEIGHT_CANVAS_BIG =
    //                      static_cast<size_t>(CellSize::Big) * 20,
    //                  WIDTH_CANVAS_SMALL =
    //                      static_cast<size_t>(CellSize::Small) * 10,
    //                  HEIGHT_CANVAS_SMALL =
    //                      static_cast<size_t>(CellSize::Small) * 20;
    //
    // QColor getQColor(AbstractGameDisplay::Color col,
    //                  AbstractGameDisplay::SelfCellType selfCellType) {
    //
    //     QColor returnValue = QColor::fromRgb(0, 0, 255);
    //
    //     switch (col) {
    //     case AbstractGameDisplay::Color::Black:
    //         returnValue = QColor::fromRgb(0, 0, 0);
    //         break;
    //     case AbstractGameDisplay::Color::White:
    //         returnValue = QColor::fromRgb(255, 255, 255);
    //         break;
    //     case AbstractGameDisplay::Color::Grey:
    //         returnValue = QColor::fromRgb(160, 160, 160);
    //         break;
    //     case AbstractGameDisplay::Color::DarkBlue:
    //         returnValue = QColor::fromRgb(0, 0, 153);
    //         break;
    //     case AbstractGameDisplay::Color::LightBlue:
    //         returnValue = QColor::fromRgb(51, 255, 255);
    //         break;
    //     case AbstractGameDisplay::Color::Purple:
    //         returnValue = QColor::fromRgb(153, 0, 153);
    //         break;
    //     case AbstractGameDisplay::Color::Red:
    //         returnValue = QColor::fromRgb(255, 0, 0);
    //         break;
    //     case AbstractGameDisplay::Color::Orange:
    //         returnValue = QColor::fromRgb(255, 153, 51);
    //         break;
    //     case AbstractGameDisplay::Color::Pink:
    //         returnValue = QColor::fromRgb(255, 102, 178);
    //         break;
    //     case AbstractGameDisplay::Color::Green:
    //         returnValue = QColor::fromRgb(128, 155, 0);
    //         break;
    //     case AbstractGameDisplay::Color::Yellow:
    //         returnValue = QColor::fromRgb(255, 255, 0);
    //         break;
    //     };
    //
    //     if (selfCellType == AbstractGameDisplay::SelfCellType::Preview) {
    //         returnValue = QColor::fromRgb(128, 128, 128, 200);
    //     }
    //
    //     return returnValue;
    // }

    GameDisplay::GameDisplay(Controller &controller, MainGui &mainGui,
                             QWidget *parent)
        : QWidget(parent), AbstractGameDisplay(controller), mainGui_(mainGui) {
        setup();
    }

    // // private methods
    //
    // void GameDisplay::playerInfo() {
    //     playerInfo_.setText(QString::fromStdString(
    //         getSelfUsername() + " : " + std::to_string(getSelfScore())));
    //
    //     playerInfo_.setText(QString::fromStdString(std::format(
    //         "{} : {}", getSelfUsername(), std::to_string(getSelfScore()))));
    //     playerInfo_.setFixedWidth(PLAYER_INFO_LABEL_WIDTH);
    // }
    //
    // void GameDisplay::energy() {
    //
    //     energy_.setRange(0, 100);
    //     energy_.setValue(static_cast<int>(round(getSelfEnergy())) * 100);
    // }
    //
    // // void GameDisplay::availableEffects();
    //
    // // void GameDisplay::penaltyInfo() {
    //
    // // }
    //
    // // void GameDisplay::bonusInfo();
    //
    // void GameDisplay::holdTetromino() {
    //     size_t cellSize = static_cast<size_t>(CellSize::Big);
    //     size_t width = ATetromino::MAX_DIMENSION * cellSize;
    //     size_t height = ATetromino::MAX_DIMENSION * cellSize;
    //
    //     if (holdTetromino_.isNull())
    //         holdTetromino_ = QImage(width, height, QImage::Format_ARGB32);
    //
    //     size_t xOffset = cellSize;
    //     size_t yOffset = cellSize;
    //
    //     const client::Tetromino *pHoldTetromino = getHoldTetromino();
    //     if (pHoldTetromino != nullptr) {
    //         QColor color =
    //         getQColor(colorIdToColor(pHoldTetromino->colorId));
    //
    //         for (const Vec2 &relCoord : pHoldTetromino->body) {
    //             int x = relCoord.getX() * cellSize + xOffset;
    //             int y = relCoord.getY() * cellSize + yOffset;
    //
    //             for (size_t dy = 0; dy < cellSize; ++dy) {
    //                 for (size_t dx = 0; dx < cellSize; ++dx) {
    //                     holdTetromino_.setPixelColor(x + dx, y + dy, color);
    //                 }
    //             }
    //         }
    //     }
    // }
    //
    // void GameDisplay::leftPane() {
    //     if (isSpectating()) {
    //         leftPane_->addWidget(quitButton_);
    //     } else {
    //         playerInfo();
    //         holdTetromino();
    //         // penaltyInfo();
    //
    //         leftPane_->addWidget(quitButton_);
    //         leftPane_->addWidget(playerInfo_);
    //         if (getGameMode() == GameMode::RoyalCompetition) {
    //             // bonusInfo();
    //             energy();
    //             // availableEffects();
    //             leftPane_->addWidget(energy_);
    //             // leftPane_->addWidget(effectsLayout_);
    //             // leftPane_->addWidget(bonus_);
    //         }
    //         // leftPane_->addWidget(penalty_);
    //
    //         QLabel *holdTetrominoLabel_ = new QLabel;
    //         holdTetrominoLabel_->setPixmap(QPixmap::fromImage(holdTetromino_));
    //
    //         leftPane_->addWidget(holdTetrominoLabel_);
    //     }
    // }
    //
    // void GameDisplay::drawBoard(CellSize size) {
    //
    //     size_t height = getBoardHeight();
    //     size_t width = getBoardWidth();
    //     size_t cellSize = static_cast<size_t>(size);
    //
    //     // maybe not working because this format only works with color
    //     palette if (selfBoard_.isNull())
    //         selfBoard_ = QImage(cellSize * width, cellSize * height,
    //                             QImage::Format_ARGB32);
    //
    //     for (uint32_t y = 0; y < height; ++y) {
    //         for (uint32_t x = 0; x < width; ++x) {
    //             QColor color =
    //                 selfCellInfoAt(x, y)
    //                     .transform([](auto cellInfo) {
    //                         return getQColor(colorIdToColor(cellInfo.first),
    //                                          cellInfo.second);
    //                     })
    //                     .value_or(getQColor(Color::Black));
    //
    //             for (uint32_t dy = 0; dy < cellSize; ++dy) {
    //                 for (uint32_t dx = 0; dx < cellSize; ++dx) {
    //                     selfBoard_.setPixelColor(
    //                         x * cellSize + dx, (height - 1 - y) * cellSize +
    //                         dy, color);
    //                 }
    //             }
    //         }
    //     }
    // }
    //
    // void GameDisplay::tetrominoQueue() {
    //     size_t queueSize = getTetrominoQueuesSize();
    //     if (queueSize == 0) {
    //         return;
    //     }
    //
    //     size_t cellSize = static_cast<size_t>(CellSize::Big);
    //     size_t width = ATetromino::MAX_DIMENSION * cellSize;
    //     size_t height = queueSize * cellSize * ATetromino::MAX_DIMENSION;
    //
    //     if (tetrominoQueue_.isNull())
    //         tetrominoQueue_ = QImage(width, height, QImage::Format_ARGB32);
    //
    //     const client::Tetromino &nextTetromino = getTetrominoQueueNth(0);
    //     size_t highestBlockY =
    //         std::max_element(nextTetromino.body.begin(),
    //                          nextTetromino.body.end(),
    //                          [](const Vec2 &a, const Vec2 &b) {
    //                              return a.getY() > b.getY();
    //                          })
    //             ->getY();
    //
    //     size_t yInitialOffset = highestBlockY * cellSize;
    //
    //     for (size_t idx = 0; idx < queueSize; ++idx) {
    //         const client::Tetromino &tetromino = getTetrominoQueueNth(idx);
    //         const std::vector<Vec2> &body = tetromino.body;
    //
    //         // x-offset
    //         size_t leftmostBlockX =
    //             -std::min_element(body.begin(), body.end(),
    //                               [](const Vec2 &a, const Vec2 &b) {
    //                                   return a.getX() < b.getX();
    //                               })
    //                  ->getX();
    //
    //         size_t xOffset = leftmostBlockX * cellSize;
    //
    //         // y-offset
    //         size_t yOffset =
    //             idx * ATetromino::MAX_DIMENSION * cellSize - yInitialOffset;
    //
    //         QColor color = getQColor(colorIdToColor(tetromino.colorId));
    //
    //         for (const auto &vec : body) {
    //             int x = vec.getX() * cellSize + xOffset;
    //             int y = vec.getY() * cellSize + yOffset;
    //
    //             for (size_t dy = 0; dy < cellSize; ++dy) {
    //                 for (size_t dx = 0; dx < cellSize; ++dx) {
    //                     tetrominoQueue_.setPixelColor(x + dx, y + dy, color);
    //                 }
    //             }
    //         }
    //     }
    // }
    //
    // void GameDisplay::middlePane() {
    //     drawBoard();
    //     QLabel *selfBoardLabel_ = new QLabel;
    //     selfBoardLabel_->setPixmap(QPixmap::fromImage(selfBoard_));
    //
    //     if (isSpectating()) {
    //         middlePane_->addWidget(mode_);
    //         middlePane_->addWidget(selfBoardLabel_);
    //     } else {
    //         tetrominoQueue();
    //         QLabel *tetrominoQueueLabel_ = new QLabel;
    //         tetrominoQueueLabel_->setPixmap(
    //             QPixmap::fromImage(tetrominoQueue_));
    //
    //         QHBoxLayout *wrapper = new QHBoxLayout;
    //         QVBoxLayout *board = new QVBoxLayout;
    //
    //         board->addWidget(mode_);
    //         board->addWidget(selfBoardLabel_);
    //
    //         wrapper->addWidget(board);
    //         wrapper->addWidget(tetrominoQueueLabel_);
    //
    //         middlePane_->addWidget(wrapper);
    //     }
    // }
    //
    // void GameDisplay::createOpBoardDisplay(size_t index, CellSize size) {
    //     size_t height = getBoardHeight();
    //     size_t width = getBoardWidth();
    //     size_t cellSize = static_cast<size_t>(size);
    //
    //     for (uint32_t y = 0; y < height; ++y) {
    //         for (uint32_t x = 0; x < width; ++x) {
    //
    //             QColor color = getQColor(
    //                 opponentsBoardGetColorIdAt(index, x, y)
    //                     .transform([](auto id) { return colorIdToColor(id);
    //                     }) .value_or(Color::Black));
    //
    //             for (uint32_t dy = 0; dy < cellSize; ++dy) {
    //                 for (uint32_t dx = 0; dx < cellSize; ++dx) {
    //                     opBoards_.at(index).setPixelColor(
    //                         x * cellSize + dx, (height - 1 - y) * cellSize +
    //                         dy, color);
    //                 }
    //             }
    //         }
    //     }
    // }
    //
    // void GameDisplay::opponentsBoard() {
    //
    //     CellSize cellSize =
    //         (getGameMode() == GameMode::Dual) ? CellSize::Big :
    //         CellSize::Small;
    //
    //     for (size_t index = 0; index < getNumOpponents(); index++) {
    //
    //         // auto button = ftxui::Button(
    //         //     getOpponentUsername(index),
    //         //     [index, this] {
    //         //         controller_.selectTarget(getNthOpponentUserID(index));
    //         //     },
    //         //     ftxui::ButtonOption::Animated(ftxui::Color::Yellow1));
    //
    //         if (getSelectedTarget() == getNthOpponentUserID(index)) {
    //             // button = button | ftxui::borderDouble;
    //         } else {
    //             // button = button | ftxui::borderLight;
    //         }
    //
    //         //     opponentsBoards.emplace_back( //
    //         //         ftxui::Container::Vertical({
    //         //             createOpBoardDisplay(index, cellSize),
    //         //             button,
    //         //         }));
    //     }
    // }
    //
    // void GameDisplay::rightPane() {
    //     opponentsBoard();
    //
    //     size_t numCols = 4;
    //     size_t numRows = (opSingularDisplay_.size() + numCols - 1) / numCols;
    //
    //     for (size_t rowIdx = 0; rowIdx < numRows; rowIdx++) {
    //         // ftxui::Components row;
    //         for (size_t j = 0;
    //              j < numCols
    //              && rowIdx * numCols + j < opSingularDisplay_.size();
    //              ++j) {
    //             opLayout_.addWidget(opSingularDisplay_.at(rowIdx * numCols +
    //             j),
    //                                 rowIdx, j);
    //         }
    //     }
    // }
    //
    // void GameDisplay::drawMainLayout() {
    //     leftPane();
    //     middlePane();
    //
    //     mainLayout_->addWidget(leftPane_);
    //     mainLayout_->addWidget(middlePane_);
    //
    //     if (!isSpectating() && getGameMode() != GameMode::Endless) {
    //         rightPane();
    //         mainLayout_->addWidget(opLayout_);
    //     }
    //
    //     setLayout(mainLayout_);
    // }

    // void GameDisplay::drawGameOver(){

    //     //Creat new space
    //     //The layout is directly charged
    //    QVBoxLayout *layout = new QVBoxLayout(this);

    //     //Creat label for the text
    //    QLabel *label = new QLabel("Game Over");

    //     //Choose the police
    //    QFont font("Arial", 30, QFont::Bold); // Police Arial, taille 50, gras
    //    label->setFont(font);

    //     //Center the text
    //    label->setAlignment(Qt::AlignCenter);

    //     //Add the QLabel to the layout
    //    layout->addWidget(label);
    // };

    // void GameDisplay::drawWin(){
    //     //     Creat new space
    //     // The layout is directly charged
    //    QVBoxLayout *layout = new QVBoxLayout(this);

    //     // Creat label for the text
    //    QLabel *label = new QLabel("The game is won");

    //     // Choose the police
    //    QFont font("Arial", 30, QFont::Bold); // Police Arial, taille 50, gras
    //    label->setFont(font);

    //     // Center the text
    //    label->setAlignment(Qt::AlignCenter);

    //     // Add the QLabel to the layout
    //    layout->addWidget(label);
    // };

    // void GameDisplay::handleKeys(QKeyEvent *event);

    // void GameDisplay::updateScreen(){
    //      repaint();
    // }

    QColor getQColor(AbstractGameDisplay::Color color) {
        QColor returnValue;

        switch (color) {
        case AbstractGameDisplay::Color::Black:
            returnValue = Qt::black;
            break;
        case AbstractGameDisplay::Color::White:
            returnValue = Qt::white;
            break;
        case AbstractGameDisplay::Color::Grey:
            returnValue = Qt::gray;
            break;
        case AbstractGameDisplay::Color::DarkBlue:
            returnValue = Qt::darkBlue;
            break;
        case AbstractGameDisplay::Color::LightBlue:
            returnValue = Qt::blue;
            break;
        case AbstractGameDisplay::Color::Purple:
            returnValue = Qt::magenta;
            break;
        case AbstractGameDisplay::Color::Red:
            returnValue = Qt::red;
            break;
        case AbstractGameDisplay::Color::Orange:
            returnValue = QColorConstants::Svg::orange;
            break;
        case AbstractGameDisplay::Color::Pink:
            returnValue = QColorConstants::Svg::pink;
            break;
        case AbstractGameDisplay::Color::Green:
            returnValue = Qt::green;
            break;
        case AbstractGameDisplay::Color::Yellow:
            returnValue = Qt::yellow;
            break;
        };

        return returnValue;
    }

    void GameDisplay::tetrominoQueue() {
        size_t queueSize = getTetrominoQueuesSize();

        size_t cellSize = static_cast<size_t>(CellSize::Big);
        size_t width = ATetromino::MAX_DIMENSION;
        size_t height = queueSize * ATetromino::MAX_DIMENSION;

        QPixmap tetrominoQueueMap(width * cellSize, height * cellSize);
        QPainter painter(&tetrominoQueueMap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        tetrominoQueueMap.fill(Qt::black);

        const client::Tetromino &nextTetromino = getTetrominoQueueNth(0);
        size_t highestBlockY =
            std::max_element(nextTetromino.body.begin(),
                             nextTetromino.body.end(),
                             [](const Vec2 &a, const Vec2 &b) {
                                 return a.getY() > b.getY();
                             })
                ->getY();

        size_t yInitialOffset = highestBlockY * cellSize;

        for (size_t idx = 0; idx < queueSize; ++idx) {
            const client::Tetromino &tetromino = getTetrominoQueueNth(idx);
            const std::vector<Vec2> &body = tetromino.body;

            // x-offset
            size_t leftmostBlockX =
                -std::min_element(body.begin(), body.end(),
                                  [](const Vec2 &a, const Vec2 &b) {
                                      return a.getX() < b.getX();
                                  })
                     ->getX();

            size_t xOffset = leftmostBlockX * cellSize;

            // y-offset
            size_t yOffset =
                idx * ATetromino::MAX_DIMENSION * cellSize - yInitialOffset;

            QColor color = getQColor(colorIdToColor(tetromino.colorId));
            painter.setBrush(color);
            painter.setPen(Qt::NoPen);

            for (const auto &vec : body) {
                int x = vec.getX() * cellSize + xOffset;
                int y = vec.getY() * cellSize + yOffset;

                painter.drawRect(QRect(x, y, cellSize, cellSize));
            }
        }

        tetrominoQueue_.setPixmap(tetrominoQueueMap);
    }

    void GameDisplay::on_QuitButtonClicked() {
        controller_.quitGame();
        emit backToMainMenu();
    }

    void GameDisplay::energyLCD() {
        scoreLCD_.display(static_cast<int>(getSelfScore()));
        scoreLCD_.setSegmentStyle(QLCDNumber::Filled);
    }

    void GameDisplay::scoreLCD() {
        energyLCD_.display(static_cast<int>(getSelfEnergy()));
        energyLCD_.setSegmentStyle(QLCDNumber::Filled);
    }

    void GameDisplay::selfBoard(CellSize size) {
        size_t cellSize = static_cast<size_t>(size);
        size_t height = getBoardHeight();
        size_t width = getBoardWidth();

        QPixmap selfBoardMap(cellSize * width, cellSize * height);

        QPainter painter(&selfBoardMap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        selfBoardMap.fill(Qt::black);

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {
                auto optPair = selfCellInfoAt(x, y);
                if (!optPair.has_value()) {
                    continue;
                }

                auto [colorId, cellType] = optPair.value();

                bool isPreview = (cellType == SelfCellType::Preview);

                QColor color = getQColor(colorIdToColor(colorId));

                if (isPreview) {
                    painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap,
                                        Qt::RoundJoin));
                    painter.setBrush(Qt::NoBrush);
                } else {
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(color);
                }

                painter.drawRect(QRect(x * cellSize,
                                       (height - 1 - y) * cellSize, cellSize,
                                       cellSize));
            }
        }

        painter.end();

        selfBoard_.setPixmap(selfBoardMap);
    }

    void GameDisplay::holdTetromino() {
        size_t cellSize = static_cast<size_t>(CellSize::Big);
        size_t width = ATetromino::MAX_DIMENSION;
        size_t height = ATetromino::MAX_DIMENSION;

        QPixmap holdTetrominoMap(width * cellSize, height * cellSize);
        QPainter painter(&holdTetrominoMap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        holdTetrominoMap.fill(Qt::black);

        size_t xOffset = cellSize;
        size_t yOffset = cellSize;

        const client::Tetromino *pHoldTetromino = getHoldTetromino();
        if (pHoldTetromino != nullptr) {
            QColor color = getQColor(colorIdToColor(pHoldTetromino->colorId));
            painter.setBrush(color);
            painter.setPen(Qt::NoPen);

            for (const Vec2 &relCoord : pHoldTetromino->body) {
                int x = relCoord.getX() * cellSize + xOffset;
                int y = relCoord.getY() * cellSize + yOffset;

                painter.drawRect(QRect(x, y, cellSize, cellSize));
            }
        }

        painter.end();

        holdTetromino_.setPixmap(holdTetrominoMap);
    }

    void GameDisplay::keyPressEvent(QKeyEvent *event) {
        std::string keyPressed;

        switch (event->key()) {
        case Qt::Key_Left:
            keyPressed = "ArrowLeft";
            break;
        case Qt::Key_Right:
            keyPressed = "ArrowRight";
            break;
        case Qt::Key_Down:
            keyPressed = "ArrowDown";
            break;
        case Qt::Key_Space:
            keyPressed = "Space";
            break;
        default:
            keyPressed = event->text().toStdString();
        }

        controller_.handleKeypress(keyPressed);
    }

    void GameDisplay::updateGameState() {
        gameState_ = controller_.getGameState();

        selfBoard();
        scoreLCD();
        holdTetromino();
        tetrominoQueue();

        if (getGameMode() == GameMode::RoyalCompetition) {
            energyLCD();
        }
    }

    void GameDisplay::setup() {
        setFocusPolicy(Qt::StrongFocus);

        // ------------FIRST_SPACERS------------

        leftPane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                          QSizePolicy::Expanding));
        middlePane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        rightPane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                           QSizePolicy::Expanding));

        // ------------LEFT_PANE----------------

        QPushButton *quitButton = new QPushButton{tr("&Quit")};

        leftPane_.addWidget(quitButton);
        leftPane_.addWidget(&scoreLCD_);
        if (getGameMode() == GameMode::RoyalCompetition) {
            leftPane_.addWidget(&energyLCD_);
        }
        leftPane_.addWidget(&holdTetromino_);

        // ------------MIDDLE_PANE---------------

        QLabel *gameMode =
            new QLabel{QString::fromStdString(toString(getGameMode()))};

        middlePane_.addWidget(gameMode);
        middlePane_.addWidget(&selfBoard_);

        // ------------RIGHT_PANE----------------

        rightPane_.addWidget(&tetrominoQueue_);

        // ------------END_SPACERS--------------

        leftPane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                          QSizePolicy::Expanding));
        middlePane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        rightPane_.addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                           QSizePolicy::Expanding));

        // ------------SPLIT_3_PANES-------------

        mainLayout_.addLayout(&leftPane_);
        mainLayout_.addLayout(&middlePane_);
        mainLayout_.addLayout(&rightPane_);

        // --------------------------------------

        setLayout(&mainLayout_);

        connect(&mainGui_, &MainGui::updateGameState, this,
                &GameDisplay::updateGameState);

        connect(quitButton, &QPushButton::clicked, this,
                &GameDisplay::on_QuitButtonClicked);
    }

} // namespace GUI
