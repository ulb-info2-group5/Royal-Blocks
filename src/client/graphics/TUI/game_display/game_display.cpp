#include "game_display.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include "board/board.hpp"
#include "effect/effect_type.hpp"
#include "effect/penalty/timed_penalty.hpp"
#include "effect_price/effect_price.hpp"
#include "game_mode/game_mode.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_tui.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/pixel.hpp>
#include <optional>
#include <stdexcept>
#include <string>

Color colorIdToColor(unsigned colorID) {
    // TODO: remove those magic number
    switch (colorID) {
    case 0:
        return Color::Red;
    case 1:
        return Color::Orange;
    case 2:
        return Color::Yellow;
    case 3:
        return Color::Green;
    case 4:
        return Color::LightBlue;
    case 5:
        return Color::DarkBlue;
    case 6:
        return Color::Purple;
    case 8: // MINI_TETROMINO
        return Color::Pink;
    case PENALTY_BLOCKS_COLOR_ID:
        return Color::Grey;

    default:
        throw std::runtime_error{"unknown color"};
    };
}

ftxui::Color getFTXUIColor(Color color, GameDisplay::SelfCellType selfCellType =
                                            GameDisplay::SelfCellType::Placed) {
    ftxui::Color returnValue = ftxui::Color::Blue;

    switch (color) {
    case Color::Black:
        returnValue = ftxui::Color::Black;
        break;
    case Color::White:
        returnValue = ftxui::Color::White;
        break;
    case Color::Grey:
        returnValue = ftxui::Color::Grey0;
        break;
    case Color::DarkBlue:
        returnValue = ftxui::Color::Blue3;
        break;
    case Color::LightBlue:
        returnValue = ftxui::Color::Blue1;
        break;
    case Color::Purple:
        returnValue = ftxui::Color::Purple3;
        break;
    case Color::Red:
        returnValue = ftxui::Color::Red;
        break;
    case Color::Orange:
        returnValue = ftxui::Color::Orange1;
        break;
    case Color::Pink:
        returnValue = ftxui::Color::Pink1;
        break;
    case Color::Green:
        returnValue = ftxui::Color::Green1;
        break;
    case Color::Yellow:
        returnValue = ftxui::Color::Yellow1;
        break;
    };

    if (selfCellType == GameDisplay::SelfCellType::Preview) {
        returnValue =
            ftxui::Color::Blend(returnValue, ftxui::Color::RGB(128, 128, 128));
    }

    return returnValue;
}

GameDisplay::GameDisplay(MainTui &mainTui, Controller &controller)
    : mainTui_(mainTui), controller_(controller) {}

//----------------------------------------------------------------------------
//                          Left Pane
//----------------------------------------------------------------------------

ftxui::Component &GameDisplay::playerInfo() {
    playerInfo_ = ftxui::Renderer([&] {
        return ftxui::vbox(
                   {ftxui::text("Score : " + std::to_string(getSelfScore()))
                        | ftxui::center,
                    ftxui::text(getSelfUsername()) | ftxui::center})
               | ftxui::borderDashed;
    });

    return playerInfo_;
}

ftxui::Component &GameDisplay::availableEffects() {
    if (!availableEffects_) {
        availableEffects_ = ftxui::Container::Vertical({});
    }

    availableEffects_->DetachAllChildren();

    std::vector<std::pair<EffectType, Energy>> effectPrices = getEffectPrices();

    for (auto [effectType, effectPrice] : effectPrices) {
        availableEffects_->Add(ftxui::Button(
            toString(effectType) + " " + std::to_string(effectPrice),
            [effectType, this]() { controller_.buyEffect(effectType); },
            GlobalButtonStyle()));
    }

    return availableEffects_;
}

ftxui::Component &GameDisplay::energy() {
    energy_ = ftxui::Renderer([this] {
        std::vector<std::pair<EffectType, Energy>> effectPrices =
            getEffectPrices();

        return ftxui::vbox(
            {ftxui::text("Energy : " + std::to_string(getSelfEnergy()))
             | ftxui::borderRounded});
    });

    return energy_;
}

ftxui::Component &GameDisplay::penaltyInfo() {
    penaltyInfo_ = ftxui::Renderer([this] {
        std::string penaltyName;
        double elapsedTime;

        if (gameState_.self.playerState.activePenalty.has_value()) {
            const client::TimedPenalty &penalty =
                gameState_.self.playerState.activePenalty.value();

            penaltyName = toString(penalty.penaltyType);
            elapsedTime = penalty.elapsedTime;
        } else {
            penaltyName = "";
            elapsedTime = 0;
        }

        return ftxui::vbox({ftxui::text("Penalty : " + penaltyName),
                            ftxui::gaugeRight(elapsedTime)
                                | ftxui::color(ftxui::Color::Red)
                                | ftxui::borderRounded});
    });

    return penaltyInfo_;
}

ftxui::Component &GameDisplay::bonusInfo() {
    bonusInfo_ = ftxui::Renderer([this] {
        std::string bonusName;
        double elapsedTime;

        if (gameState_.self.playerState.activeBonus.has_value()) {
            const client::TimedBonus &bonus =
                gameState_.self.playerState.activeBonus.value();

            bonusName = toString(bonus.bonusType);
            elapsedTime = bonus.elapsedTime;
        } else {
            bonusName = "";
            elapsedTime = 0;
        }

        return ftxui::vbox({ftxui::text("Bonus : " + bonusName),
                            ftxui::gaugeRight(elapsedTime)
                                | ftxui::color(ftxui::Color::Green)
                                | ftxui::borderRounded});
    });

    return bonusInfo_;
}

ftxui::Component &GameDisplay::quitButton() {
    quitButton_ = ftxui::Button(
        std::string(STR_QUIT_GAME),
        [&] {
            controller_.quitGame();
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    return quitButton_;
}

ftxui::Component &GameDisplay::leftPane() {
    if (getGameMode() == GameMode::RoyalCompetition) {
        leftPane_ = ftxui::Container::Vertical({
            quitButton(),
            playerInfo(),
            energy(),

            penaltyInfo(),
            bonusInfo(),

            availableEffects(),

        });
    } else {
        leftPane_ = ftxui::Container::Vertical({
            quitButton(),
            playerInfo(),
        });
    }

    return leftPane_;
}

//----------------------------------------------------------------------------
//                          Middle Pane
//----------------------------------------------------------------------------

ftxui::Component &GameDisplay::selfBoard(CellSize size) {
    selfBoard_ = ftxui::Container::Horizontal({});

    selfBoard_ = ftxui::Renderer([size, this] {
        size_t cellSize = static_cast<size_t>(size);

        size_t height = getBoardHeight();
        size_t width = getBoardWidth();

        ftxui::Canvas selfCanvas(cellSize * width, cellSize * height);

        ftxui::Pixel pixel{};

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {

                pixel.background_color =
                    selfCellInfoAt(x, y)
                        .transform([](auto cellInfo) {
                            return getFTXUIColor(colorIdToColor(cellInfo.first),
                                                 cellInfo.second);
                        })
                        .value_or(getFTXUIColor(Color::Black));

                for (uint32_t dy = 0; dy < cellSize; ++dy) {
                    for (uint32_t dx = 0; dx < cellSize; ++dx) {
                        selfCanvas.DrawBlock(x * cellSize + dx,
                                             (height - 1 - y) * cellSize + dy,
                                             true, pixel.background_color);
                    }
                }
            }
        }

        return ftxui::canvas(selfCanvas) | ftxui::border | ftxui::center;
    });

    return selfBoard_;
}

ftxui::Component &GameDisplay::gameMode() {
    gameMode_ = ftxui::Renderer([&] {
        return ftxui::text(toString(getGameMode())) | ftxui::center
               | ftxui::border;
    });

    return gameMode_;
}

ftxui::Component &GameDisplay::middlePane() {
    middlePane_ = ftxui::Container::Vertical({
        gameMode()
            | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, WIDTH_CANVAS_BIG / 2)
            | ftxui::center,
        selfBoard(),
    });

    return middlePane_;
}

//----------------------------------------------------------------------------
//                          Right Pane
//----------------------------------------------------------------------------

ftxui::Component GameDisplay::createOpBoardDisplay(size_t index,
                                                   CellSize size) {
    size_t height = getBoardHeight();
    size_t width = getBoardWidth();
    size_t cellSize = static_cast<size_t>(size);

    return ftxui::Renderer([index, cellSize, width, height, this] {
        ftxui::Canvas opCanvas(cellSize * width, cellSize * height);

        ftxui::Pixel pixel{};

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {

                pixel.background_color = getFTXUIColor(
                    opponentsBoardGetColorIdAt(index, x, y)
                        .transform([](auto id) { return colorIdToColor(id); })
                        .value_or(Color::Black));

                for (uint32_t dy = 0; dy < cellSize; ++dy) {
                    for (uint32_t dx = 0; dx < cellSize; ++dx) {
                        opCanvas.DrawBlock(x * cellSize + dx,
                                           (height - 1 - y) * cellSize + dy,
                                           true, pixel.background_color);
                    }
                }
            }
        }

        return ftxui::canvas(opCanvas) | ftxui::border;
    });
}

ftxui::Component &GameDisplay::opponentsBoards() {
    CellSize cellSize =
        (getGameMode() == GameMode::Dual) ? CellSize::Big : CellSize::Small;

    ftxui::Components opponentsBoards;
    for (size_t index = 0; index < getNumOpponents(); index++) {

        auto button = ftxui::Button(
            getOpponentUsername(index),
            [index, this] {
                controller_.selectTarget(getNthOpponentUserID(index));
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Yellow1));

        if (getSelectedTarget() == getNthOpponentUserID(index)) {
            button = button | ftxui::borderDouble;
        } else {
            button = button | ftxui::borderLight;
        }

        opponentsBoards.emplace_back( //
            ftxui::Container::Vertical({
                createOpBoardDisplay(index, cellSize),
                button,
            }));
    }

    size_t numCols = 4;
    size_t numRows = (opponentsBoards.size() + numCols - 1) / numCols;

    opponentsBoards_ = ftxui::Container::Vertical({});

    for (size_t rowIdx = 0; rowIdx < numRows; rowIdx++) {
        ftxui::Components row;
        for (size_t j = 0;
             j < numCols && rowIdx * numCols + j < opponentsBoards.size();
             ++j) {
            row.push_back(opponentsBoards.at(rowIdx * numCols + j));
        }

        opponentsBoards_->Add(ftxui::Container::Horizontal(row));
    }

    return opponentsBoards_;
}

ftxui::Component &GameDisplay::rightPane() {
    rightPane_ = ftxui::Container::Vertical({
        opponentsBoards(),
    });

    return rightPane_;
}

ftxui::Component &GameDisplay::drawEndlessMode() {
    displayWindow_ = ftxui::Container::Horizontal({
                         leftPane(),
                         middlePane(),
                     })
                     | ftxui::center;

    return displayWindow_;
}

ftxui::Component &GameDisplay::drawMultiMode() {
    displayWindow_ = ftxui::Container::Horizontal({
                         leftPane(),
                         middlePane(),
                         rightPane(),
                     })
                     | ftxui::center;

    return displayWindow_;
}

UserID GameDisplay::getNthOpponentUserID(size_t n) const {
    return gameState_.externals.at(n).playerState.userID;
}

void GameDisplay::handleKeys() {
    displayWindow_ = ftxui::CatchEvent(displayWindow_, [&](ftxui::Event event) {
        if (event == ftxui::Event::Return) { // Keep Enter key for
                                             // his original action
            return false;
        }

        else if (event.is_mouse()) { // Do not handle mouse
                                     // events
            return false;
        }

        else { // Handle other keys
            std::string keyPressed;
            if (event == ftxui::Event::ArrowLeft) {
                keyPressed = "ArrowLeft";
            } else if (event == ftxui::Event::ArrowRight) {
                keyPressed = "ArrowRight";
            } else if (event == ftxui::Event::ArrowDown) {
                keyPressed = "ArrowDown";
            } else if (event == ftxui::Event::Character(' ')) {
                keyPressed = "Space";
            } else if (!event.character().empty()) {
                keyPressed = event.input();
            }
            controller_.handleKeypress(keyPressed);
            return true;
        }
    });
}

ftxui::Component &GameDisplay::drawGameOver() {
    ftxui::Component title =
        ftxui::Renderer([] { return GAME_OVER_TITLE | ftxui::center; });

    ftxui::Component scoreText = ftxui::Renderer([&] {
        return ftxui::text("Your score was: " + std::to_string(getSelfScore()))
               | ftxui::center;
    });

    ftxui::Component button = ftxui::Button(
        std::string(STR_RETURN_TO_MAIN_MENU), [&] { mainTui_.stopRender(); },
        GlobalButtonStyle());

    displayWindow_ = ftxui::Container::Vertical({
        title,
        ftxui::Renderer([] { return ftxui::separator(); }),
        scoreText,
        ftxui::Renderer([] { return ftxui::separator(); }),
        button,
    });

    return displayWindow_;
}

ftxui::Component &GameDisplay::drawWin() {
    ftxui::Component title =
        ftxui::Renderer([] { return YOU_WIN_TITLE | ftxui::center; });

    ftxui::Component scoreText = ftxui::Renderer([&] {
        return ftxui::text("Your score was: " + std::to_string(getSelfScore()))
               | ftxui::center;
    });

    ftxui::Component button = ftxui::Button(
        std::string(STR_RETURN_TO_MAIN_MENU), [&] { mainTui_.stopRender(); },
        GlobalButtonStyle());

    displayWindow_ = ftxui::Container::Vertical({
        title,
        ftxui::Renderer([] { return ftxui::separator(); }),
        scoreText,
        ftxui::Renderer([] { return ftxui::separator(); }),
        button,
    });

    return displayWindow_;
}

void GameDisplay::render() {
    ftxui::Component gameContainer = ftxui::Container::Vertical({});

    bool isWinner = true;

    auto updateGame = [&] {
        gameContainer->DetachAllChildren();

        gameState_ = controller_.getGameState();

        if (gameState_.isFinished) {
            if (getGameMode() == GameMode::Endless || !isWinner) {
                gameContainer->Add(drawGameOver());
            } else {
                gameContainer->Add(drawWin());
            }

            return;
        }

        isWinner = gameState_.self.playerState.isAlive;

        if (getGameMode() == GameMode::Endless) {
            drawEndlessMode();
        } else {
            drawMultiMode();
        }

        handleKeys();

        gameContainer->Add(displayWindow_);
    };

    ftxui::Component render =
        ftxui::Renderer(ftxui::Container::Vertical({
                            gameContainer,
                        }),
                        [&] {
                            updateGame();
                            return ftxui::vbox({
                                       gameContainer->Render(),
                                   })
                                   | ftxui::borderHeavy | ftxui::center;
                        });

    mainTui_.render(render);
}

size_t GameDisplay::getBoardHeight() const {
    return gameState_.self.tetris.board.getHeight();
}

size_t GameDisplay::getBoardWidth() const {
    return gameState_.self.tetris.board.getWidth();
}

Score GameDisplay::getSelfScore() const {
    return gameState_.self.playerState.score;
}

std::optional<UserID> GameDisplay::getSelectedTarget() const {
    return gameState_.self.playerState.penaltyTarget;
}

Score GameDisplay::getSelfEnergy() const {
    return gameState_.self.playerState.energy.value_or(0);
}

GameMode GameDisplay::getGameMode() const { return gameState_.gameMode; }

std::optional<std::pair<unsigned, GameDisplay::SelfCellType>>
GameDisplay::selfCellInfoAt(int x, int y) const {
    if (gameState_.self.tetris.board.get(x, y).getColorId().has_value()) {
        return std::make_pair(
            gameState_.self.tetris.board.get(x, y).getColorId().value(),
            GameDisplay::SelfCellType::Placed);
    }

    auto &activeTetromino = gameState_.self.tetris.activeTetromino;
    if (activeTetromino.has_value()) {
        for (auto &vec : activeTetromino->body) {
            if (activeTetromino->anchorPoint + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(activeTetromino->colorId,
                                   GameDisplay::SelfCellType::Active));
            }
        }
    }

    auto &previewTetromino = gameState_.self.tetris.previewTetromino;
    if (previewTetromino.has_value()) {
        for (auto &vec : previewTetromino->body) {
            if (previewTetromino->anchorPoint + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(previewTetromino->colorId,
                                   GameDisplay::SelfCellType::Preview));
            }
        }
    }

    return std::nullopt;
}

std::optional<unsigned>
GameDisplay::opponentsBoardGetColorIdAt(size_t opponentIdx, int x,
                                        int y) const {
    return gameState_.externals.at(opponentIdx)
        .tetris.board.get(x, y)
        .getColorId();
}

std::string GameDisplay::getSelfUsername() const {
    return gameState_.self.playerState.username;
}

std::string GameDisplay::getOpponentUsername(size_t opponentIdx) const {
    return gameState_.externals.at(opponentIdx).playerState.username;
}

size_t GameDisplay::getNumOpponents() const {
    return gameState_.externals.size();
}

bool GameDisplay::inGame() const { return !gameState_.isFinished; }

const std::vector<std::pair<EffectType, Energy>> &
GameDisplay::getEffectPrices() const {
    return gameState_.effectsPrice;
}
