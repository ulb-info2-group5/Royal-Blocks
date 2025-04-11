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
#include <optional>
#include <print>

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
#include <qgridlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <string>

namespace GUI {

    GameDisplay::GameDisplay(Controller &controller, MainGui &mainGui,
                             QWidget *parent)
        : QWidget(parent), AbstractGameDisplay(controller), mainGui_(mainGui) {
        setup();
    }

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

    QLabel *GameDisplay::createOppBoard(size_t index, CellSize size) {
        size_t cellSize = static_cast<size_t>(size);
        size_t height = getBoardHeight();
        size_t width = getBoardWidth();

        QLabel *oppBoard = new QLabel;
        QPixmap oppBoardMap(cellSize * width, cellSize * height);

        QPainter painter(&oppBoardMap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        oppBoardMap.fill(Qt::black);

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {

                std::optional<unsigned> opt =
                    opponentsBoardGetColorIdAt(index, x, y);

                if (!opt.has_value()) {
                    continue;
                }

                QColor color = getQColor(colorIdToColor(opt.value()));
                painter.setBrush(color);
                painter.setPen(Qt::NoPen);

                painter.drawRect(QRect(x * cellSize,
                                       (height - 1 - y) * cellSize, cellSize,
                                       cellSize));
            };
        }

        painter.end();

        oppBoard->setPixmap(oppBoardMap);

        return oppBoard;
    }

    void GameDisplay::oppBoards() {
        QLabel *helloText = new QLabel("hello");
        std::println("adding helloText");
        oppBoards_.addWidget(helloText);

        // This works, but isn't what I want.
        // rightPane_.addWidget(createOppBoard(0, CellSize::Big));

        // This should work but doesn't.
        // size_t numCols = 4;
        //
        // for (size_t i = 0; i < getNumOpponents(); ++i) {
        //
        //     CellSize cellSize = (getGameMode() == GameMode::Dual)
        //                             ? CellSize::Big
        //                             : CellSize::Small;
        //
        //     QLabel *board = createOppBoard(i, cellSize);
        //
        //     int row = static_cast<int>(i) / numCols;
        //     int col = static_cast<int>(i) % numCols;
        //     oppBoards_.addWidget(board, row, col);
        // }
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

        if (getGameMode() != GameMode::Endless) {
            oppBoards();
        }

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

        // FIXME: This is wrong in both cases:
        // If commented it will always be there in all GameModes.
        // If not commented it will never be there even in RoyalCompetition.
        // if (getGameMode() == GameMode::RoyalCompetition) {
        // leftPane_.addWidget(&energyLCD_);
        // }

        leftPane_.addWidget(&holdTetromino_);

        // ------------MIDDLE_PANE---------------

        QLabel *gameMode =
            new QLabel{QString::fromStdString(toString(getGameMode()))};

        middlePaneLeftVBox_.addWidget(gameMode);
        middlePaneLeftVBox_.addWidget(&selfBoard_);

        middlePaneHBox_.addLayout(&middlePaneLeftVBox_);
        middlePaneHBox_.addWidget(&tetrominoQueue_);

        middlePane_.addLayout(&middlePaneHBox_);

        // ------------RIGHT_PANE----------------

        // if (getGameMode() != GameMode::Endless) {
        std::println("adding oppBoards_ layout");
        rightPane_.addLayout(&oppBoards_);
        // }

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
