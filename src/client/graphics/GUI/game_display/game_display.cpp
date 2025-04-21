#include "game_display.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "../qt_config/qt_config.hpp"
#include "effect/effect_type.hpp"
#include "effect_info.hpp"
#include "game_mode/game_mode.hpp"
#include "graphics/GUI/game_display/opponents_grid.hpp"
#include "graphics/common/abstract_game_display.hpp"
#include "vec2/vec2.hpp"

#include <optional>
#include <string>

#include <QBoxLayout>
#include <QChar>
#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace GUI {

    GameDisplay::GameDisplay(Controller &controller, TetrisWindow &tetrisWindow,
                             QWidget *parent)
        : QWidget(parent), AbstractGameDisplay(controller),
          tetrisWindow_(tetrisWindow) {
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

    QPixmap *GameDisplay::createOppBoardMap(size_t index, CellSize size) {
        size_t cellSize = static_cast<size_t>(size);
        size_t height = getBoardHeight();
        size_t width = getBoardWidth();

        QPixmap *oppBoardMap = new QPixmap(cellSize * width, cellSize * height);

        QPainter painter(oppBoardMap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        oppBoardMap->fill(Qt::black);

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

        return oppBoardMap;
    }

    void GameDisplay::oppBoards() {
        size_t numOpponents = getNumOpponents();

        opponentsGrid_.setNumOpponents(numOpponents);

        for (size_t i = 0; i < numOpponents; ++i) {
            CellSize cellSize = (getGameMode() == GameMode::Dual)
                                    ? CellSize::Big
                                    : CellSize::Small;

            QPixmap *opponentBoardMap = createOppBoardMap(i, cellSize);

            opponentsGrid_.setNthOpponent(
                i, opponentBoardMap,
                QString::fromStdString(getOpponentUsername(i)));

            if (!isSpectating()) {
                bool isSelected =
                    getSelectedTarget() == getNthOpponentUserID(i);
                if (isSelected) {
                    opponentsGrid_.setSelectedTarget(i);
                }
            }
        }
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

    void GameDisplay::on_TargetSelected(size_t targetIdx) {
        if (!isSpectating()) {
            selectTarget(targetIdx);
        }
    }

    void GameDisplay::on_EffectBought(EffectType effect) {
        setSelectedEffectType(effect);
        buyEffect(effect);
    }

    void GameDisplay::on_QuitButtonClicked() {
        quitGame();
        emit backToMainMenu();
    }

    void GameDisplay::scoreLCD() {
        scoreLCD_.display(static_cast<int>(getSelfScore()));
        scoreLCD_.setSegmentStyle(QLCDNumber::Filled);
    }

    void GameDisplay::energyLCD() {
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

        handleKeyPress(keyPressed);
    }

    void GameDisplay::updateGameState() {
        AbstractGameDisplay::updateGameState();

        if (gameIsFinished()) {
            QPushButton *returnToMainMenuButton =
                new QPushButton("Return to Main Menu");
            returnToMainMenuButton->setFixedWidth(500);
            connect(returnToMainMenuButton, &QPushButton::clicked, this,
                    &GameDisplay::on_ReturnToMainMenuButtonClicked);

            QWidget *finishWidget = new QWidget();
            QVBoxLayout *finishLayout = new QVBoxLayout();
            finishLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                                  QSizePolicy::Expanding));

            if (isWinner()) {
                finishLayout->addWidget(createCenterBoldTitle("You Win !"));
            } else {
                finishLayout->addWidget(createCenterBoldTitle("Game Over"));
            }

            if (!isSpectating()) {
                finishLayout->addWidget(
                    new QLabel("Your score was : "
                               + QString::number(getSelfScore())),
                    0, Qt::AlignCenter);
            }
            finishLayout->addWidget(returnToMainMenuButton, 0, Qt::AlignCenter);
            finishLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                                  QSizePolicy::Expanding));

            finishWidget->setLayout(finishLayout);
            stackedWidget_.addWidget(finishWidget);
            stackedWidget_.setCurrentWidget(finishWidget);
            return;
        }

        if (isSpectating()) {
            selfBoard_.hide();
            scoreLCD_.hide();
            holdTetromino_.hide();
            tetrominoQueue_.hide();
        } else {
            selfBoard();
            scoreLCD();
            holdTetromino();
            tetrominoQueue();

            selfBoard_.show();
            scoreLCD_.show();
            holdTetromino_.show();
            tetrominoQueue_.show();
        }

        if (getGameMode() != GameMode::Endless || isSpectating()) {
            oppBoards();
        }

        if (getGameMode() == GameMode::RoyalCompetition && !isSpectating()) {
            energyLCD();
            effectsInfo();
            effectSelector();

            energyLCD_.show();
            bonusInfo_.show();
            penaltyInfo_.show();
            effectSelector_.show();
        } else {
            energyLCD_.hide();
            bonusInfo_.hide();
            penaltyInfo_.hide();
            effectSelector_.hide();
        }
    }

    void GameDisplay::effectSelector() {
        effectSelector_.setEffectPrices(getEffectPrices(),
                                        getSelectedEffectType());
    }

    void GameDisplay::bonusInfo() {
        auto [bonusName, elapsedTime] =
            getBonusInfo().value_or(std::make_pair(std::string{}, 0));

        bonusInfo_.setName(QString::fromStdString(bonusName));
        bonusInfo_.setProgress(elapsedTime);

        bonusInfo_.setFrameStyle(QFrame::Panel | QFrame::Raised);
        bonusInfo_.setStyleSheet("QFrame { border: 3px solid green; }");
    }

    void GameDisplay::penaltyInfo() {
        auto [penaltyName, elapsedTime] =
            getPenaltyInfo().value_or(std::make_pair(std::string{}, 0));

        penaltyInfo_.setName(QString::fromStdString(penaltyName));
        penaltyInfo_.setProgress(elapsedTime);

        penaltyInfo_.setFrameStyle(QFrame::Panel | QFrame::Raised);
        penaltyInfo_.setStyleSheet("QFrame { border: 3px solid red; }");
    }

    void GameDisplay::effectsInfo() {
        bonusInfo();
        penaltyInfo();
    }

    void GameDisplay::setup() {
        QVBoxLayout *leftPane = new QVBoxLayout();
        leftPane->setAlignment(Qt::AlignCenter);
        QVBoxLayout *middlePane = new QVBoxLayout();
        middlePane->setAlignment(Qt::AlignCenter);
        QVBoxLayout *rightPane = new QVBoxLayout();
        rightPane->setAlignment(Qt::AlignCenter);

        // ------------FIRST_SPACERS------------

        leftPane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                          QSizePolicy::Expanding));
        middlePane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        rightPane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                           QSizePolicy::Expanding));

        // ------------LEFT_PANE----------------

        QPushButton *quitButton = new QPushButton(tr("&Quit"));
        quitButton->setFocusPolicy(Qt::NoFocus);
        quitButton->setFixedWidth(100);

        scoreLCD_.setFixedWidth(100);

        leftPane->addWidget(quitButton, 0, Qt::AlignCenter);
        leftPane->addWidget(&scoreLCD_, 0, Qt::AlignCenter);

        leftPane->addWidget(&energyLCD_, 0, Qt::AlignCenter);

        leftPane->addWidget(&holdTetromino_, 0, Qt::AlignCenter);

        leftPane->addWidget(&bonusInfo_, 0, Qt::AlignCenter);
        leftPane->addWidget(&penaltyInfo_, 0, Qt::AlignCenter);

        leftPane->addWidget(&effectSelector_, 0, Qt::AlignCenter);

        // ------------MIDDLE_PANE---------------

        QLabel *gameMode =
            createCenterBoldTitle(toString(getGameMode()).c_str());

        middlePaneLeftVBox_.addWidget(gameMode, 0, Qt::AlignCenter);
        middlePaneLeftVBox_.addWidget(&selfBoard_, 0, Qt::AlignCenter);

        middlePaneHBox_.addLayout(&middlePaneLeftVBox_);
        middlePaneHBox_.addWidget(&tetrominoQueue_, 0, Qt::AlignCenter);

        middlePane->addLayout(&middlePaneHBox_);

        // ------------RIGHT_PANE----------------
        rightPane->addWidget(&opponentsGrid_, 0, Qt::AlignCenter);

        // ------------END_SPACERS--------------

        leftPane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                          QSizePolicy::Expanding));
        middlePane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        rightPane->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                           QSizePolicy::Expanding));

        // ------------SPLIT_3_PANES-------------
        QWidget *gameWidget = new QWidget(this);
        QHBoxLayout *gameLayout = new QHBoxLayout(gameWidget);

        gameLayout->addLayout(leftPane);
        gameLayout->addLayout(middlePane);
        gameLayout->addLayout(rightPane);

        // ----set StackedWidget and mainLayout----

        stackedWidget_.addWidget(gameWidget);
        stackedWidget_.setCurrentWidget(gameWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(&stackedWidget_, 0, Qt::AlignCenter);
        mainLayout->setAlignment(Qt::AlignCenter);

        setLayout(mainLayout);

        // --------------------------------------

        connect(&tetrisWindow_, &TetrisWindow::updateGameState, this,
                &GameDisplay::updateGameState);

        connect(quitButton, &QPushButton::clicked, this,
                &GameDisplay::on_QuitButtonClicked);

        connect(&effectSelector_, &EffectSelector::buyEffect, this,
                &GameDisplay::on_EffectBought);

        connect(&opponentsGrid_, &OpponentsGrid::selectTarget, this,
                &GameDisplay::on_TargetSelected);
    }

    void GameDisplay::on_ReturnToMainMenuButtonClicked() {
        emit backToMainMenu();
    }

} // namespace GUI
