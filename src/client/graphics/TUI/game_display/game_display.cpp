#include "game_display.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include "core/in_game/effects/timed_bonus.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"
#include "effect/effect_type.hpp"
#include "effect_price/effect_price.hpp"
#include "game_mode/game_mode.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_tui.hpp"
#include "graphics/common/abstract_game_display.hpp"
#include "player_state/player_state.hpp"
#include "tetromino/tetromino.hpp"
#include "vec2/vec2.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace TUI {

    ftxui::Color getFTXUIColor(AbstractGameDisplay::Color color,
                               AbstractGameDisplay::SelfCellType selfCellType =
                                   AbstractGameDisplay::SelfCellType::Placed) {
        ftxui::Color returnValue = ftxui::Color::Blue;

        switch (color) {
        case AbstractGameDisplay::Color::Black:
            returnValue = ftxui::Color::Black;
            break;
        case AbstractGameDisplay::Color::White:
            returnValue = ftxui::Color::White;
            break;
        case AbstractGameDisplay::Color::Grey:
            returnValue = ftxui::Color::Grey0;
            break;
        case AbstractGameDisplay::Color::DarkBlue:
            returnValue = ftxui::Color::Blue3;
            break;
        case AbstractGameDisplay::Color::LightBlue:
            returnValue = ftxui::Color::Blue1;
            break;
        case AbstractGameDisplay::Color::Purple:
            returnValue = ftxui::Color::Purple3;
            break;
        case AbstractGameDisplay::Color::Red:
            returnValue = ftxui::Color::Red;
            break;
        case AbstractGameDisplay::Color::Orange:
            returnValue = ftxui::Color::Orange1;
            break;
        case AbstractGameDisplay::Color::Pink:
            returnValue = ftxui::Color::Pink1;
            break;
        case AbstractGameDisplay::Color::Green:
            returnValue = ftxui::Color::Green1;
            break;
        case AbstractGameDisplay::Color::Yellow:
            returnValue = ftxui::Color::Yellow1;
            break;
        };

        if (selfCellType == AbstractGameDisplay::SelfCellType::Preview) {
            returnValue = ftxui::Color::Blend(returnValue,
                                              ftxui::Color::RGB(128, 128, 128));
        }

        return returnValue;
    }

    GameDisplay::GameDisplay(MainTui &mainTui, Controller &controller)
        : AbstractGameDisplay(controller), mainTui_(mainTui) {}

    //----------------------------------------------------------------------------
    //                          Left Pane
    //----------------------------------------------------------------------------

    ftxui::Component GameDisplay::playerInfo() {
        return ftxui::Renderer([&] {
            return ftxui::vbox(
                       {ftxui::text("Score : " + std::to_string(getSelfScore()))
                            | ftxui::center,
                        ftxui::text(getSelfUsername()) | ftxui::center})
                   | ftxui::borderDashed;
        });
    }

    ftxui::Component GameDisplay::availableEffects() {
        ftxui::Component availableEffects = ftxui::Container::Vertical({});

        std::vector<std::pair<EffectType, Energy>> effectPrices =
            getEffectPrices();

        for (auto [effectType, effectPrice] : effectPrices) {

            ftxui::Component button = ftxui::Button(
                toString(effectType) + " " + std::to_string(effectPrice),
                [this, effectType]() {
                    controller_.setSelectedEffectType(effectType);
                    controller_.buyEffect(effectType);
                },
                GlobalButtonStyle());

            availableEffects->Add(button);

            if (controller_.getSelectedEffectType() == effectType) {
                availableEffects->SetActiveChild(button);
            }
        }

        return availableEffects;
    }

    ftxui::Component GameDisplay::energy() {
        return ftxui::Renderer([this] {
            std::vector<std::pair<EffectType, Energy>> effectPrices =
                getEffectPrices();

            return ftxui::vbox(
                {ftxui::text("Energy : " + std::to_string(getSelfEnergy()))
                 | ftxui::borderRounded});
        });
    }

    ftxui::Component GameDisplay::penaltyInfo() {
        return ftxui::Renderer([this] {
            const auto &gs = std::get<client::GameState>(gameState_);

            auto [penaltyName, elapsedTime] =
                gs.self.playerState.activePenalty
                    .transform([](const client::TimedPenalty &penalty) {
                        return std::make_pair(toString(penalty.penaltyType),
                                              penalty.elapsedTime);
                    })
                    .value_or(std::make_pair(std::string{}, 0));

            return ftxui::vbox({ftxui::text("Penalty : " + penaltyName),
                                ftxui::gaugeRight(elapsedTime)
                                    | ftxui::color(ftxui::Color::Red)
                                    | ftxui::borderRounded});
        });
    }

    ftxui::Component GameDisplay::bonusInfo() {
        return ftxui::Renderer([this] {
            const auto &gs = std::get<client::GameState>(gameState_);

            auto [bonusName, elapsedTime] =
                gs.self.playerState.activeBonus
                    .transform([](const client::TimedBonus &bonus) {
                        return std::make_pair(toString(bonus.bonusType),
                                              bonus.elapsedTime);
                    })
                    .value_or(std::make_pair(std::string{}, 0));

            return ftxui::vbox({ftxui::text("Bonus : " + bonusName),
                                ftxui::gaugeRight(elapsedTime)
                                    | ftxui::color(ftxui::Color::Green)
                                    | ftxui::borderRounded});
        });
    }

    ftxui::Component GameDisplay::quitButton() {
        return ftxui::Button(
            std::string(STR_QUIT_GAME),
            [&] {
                controller_.quitGame();
                mainTui_.stopRender();
            },
            GlobalButtonStyle());
    }

    ftxui::Component GameDisplay::holdTetromino() {
        return ftxui::Renderer([this] {
            size_t cellSize = static_cast<size_t>(CellSize::Big);
            size_t width = ATetromino::MAX_DIMENSION * cellSize;
            size_t height = ATetromino::MAX_DIMENSION * cellSize;

            ftxui::Canvas canvas(width, height);

            size_t xOffset = cellSize;
            size_t yOffset = cellSize;

            const client::Tetromino *pHoldTetromino = getHoldTetromino();
            if (pHoldTetromino != nullptr) {
                ftxui::Color color =
                    getFTXUIColor(colorIdToColor(pHoldTetromino->colorId));

                for (const Vec2 &relCoord : pHoldTetromino->body) {
                    int x = relCoord.getX() * cellSize + xOffset;
                    int y = relCoord.getY() * cellSize + yOffset;

                    for (size_t dy = 0; dy < cellSize; ++dy) {
                        for (size_t dx = 0; dx < cellSize; ++dx) {
                            canvas.DrawBlock(x + dx, y + dy, true, color);
                        }
                    }
                }
            }

            return ftxui::canvas(canvas) | ftxui::border | ftxui::center;
        });
    }

    ftxui::Component GameDisplay::leftPane() {
        if (isSpectating()) {
            return ftxui::Container::Vertical({
                quitButton(),
            });
        } else if (getGameMode() == GameMode::RoyalCompetition) {
            return ftxui::Container::Vertical({
                quitButton(),
                playerInfo(),
                energy(),

                holdTetromino(),

                penaltyInfo(),
                bonusInfo(),

                availableEffects(),
            });
        } else {
            return ftxui::Container::Vertical({
                quitButton(),
                playerInfo(),

                holdTetromino(),
            });
        }
    }

    //----------------------------------------------------------------------------
    //                          Middle Pane
    //----------------------------------------------------------------------------

    ftxui::Component GameDisplay::selfBoard(CellSize size) {
        return ftxui::Renderer([size, this] {
            size_t cellSize = static_cast<size_t>(size);

            size_t height = getBoardHeight();
            size_t width = getBoardWidth();

            ftxui::Canvas selfCanvas(cellSize * width, cellSize * height);

            for (uint32_t y = 0; y < height; ++y) {
                for (uint32_t x = 0; x < width; ++x) {

                    ftxui::Color color =
                        selfCellInfoAt(x, y)
                            .transform([](auto cellInfo) {
                                return getFTXUIColor(
                                    colorIdToColor(cellInfo.first),
                                    cellInfo.second);
                            })
                            .value_or(getFTXUIColor(Color::Black));

                    for (uint32_t dy = 0; dy < cellSize; ++dy) {
                        for (uint32_t dx = 0; dx < cellSize; ++dx) {
                            selfCanvas.DrawBlock(
                                x * cellSize + dx,
                                (height - 1 - y) * cellSize + dy, true, color);
                        }
                    }
                }
            }

            return ftxui::canvas(selfCanvas) | ftxui::border | ftxui::center;
        });
    }

    ftxui::Component GameDisplay::gameMode() {
        return ftxui::Renderer([&] {
            return ftxui::text(toString(getGameMode())) | ftxui::center
                   | ftxui::border;
        });
    }

    ftxui::Component GameDisplay::tetrominoQueue() {
        return ftxui::Renderer([this] {
            size_t queueSize = getTetrominoQueuesSize();
            if (queueSize == 0) {
                return ftxui::text("Queue is empty") | ftxui::center;
            }

            size_t cellSize = static_cast<size_t>(CellSize::Big);
            size_t width = ATetromino::MAX_DIMENSION * cellSize;
            size_t height = queueSize * cellSize * ATetromino::MAX_DIMENSION;

            ftxui::Canvas canvas(width, height);

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

                ftxui::Color color =
                    getFTXUIColor(colorIdToColor(tetromino.colorId));

                for (const auto &vec : body) {
                    int x = vec.getX() * cellSize + xOffset;
                    int y = vec.getY() * cellSize + yOffset;

                    for (size_t dy = 0; dy < cellSize; ++dy) {
                        for (size_t dx = 0; dx < cellSize; ++dx) {
                            canvas.DrawBlock(x + dx, y + dy, true, color);
                        }
                    }
                }
            }

            return ftxui::canvas(canvas) | ftxui::border | ftxui::center;
        });
    }

    ftxui::Component GameDisplay::middlePane() {
        return ftxui::Container::Horizontal({
            ftxui::Container::Vertical({
                gameMode()
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL,
                                  WIDTH_CANVAS_BIG / 2)
                    | ftxui::center,
                selfBoard(),
            }),

            tetrominoQueue(),

        });
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

            for (uint32_t y = 0; y < height; ++y) {
                for (uint32_t x = 0; x < width; ++x) {

                    ftxui::Color color =
                        getFTXUIColor(opponentsBoardGetColorIdAt(index, x, y)
                                          .transform([](auto id) {
                                              return colorIdToColor(id);
                                          })
                                          .value_or(Color::Black));

                    for (uint32_t dy = 0; dy < cellSize; ++dy) {
                        for (uint32_t dx = 0; dx < cellSize; ++dx) {
                            opCanvas.DrawBlock(x * cellSize + dx,
                                               (height - 1 - y) * cellSize + dy,
                                               true, color);
                        }
                    }
                }
            }

            return ftxui::canvas(opCanvas) | ftxui::border;
        });
    }

    ftxui::Component GameDisplay::opponentsBoards() {
        CellSize cellSize =
            (getGameMode() == GameMode::Dual) ? CellSize::Big : CellSize::Small;

        ftxui::Components opponentsBoards;
        for (size_t index = 0; index < getNumOpponents(); index++) {

            auto button = ftxui::Button(
                getOpponentUsername(index)
                    + std::string{checkOpponentAlive(index) ? ""
                                                            : STR_PLAYER_DEAD},
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

        ftxui::Component opponentsBoards_ = ftxui::Container::Vertical({});

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

    ftxui::Component GameDisplay::rightPane() {
        return ftxui::Container::Vertical({
            opponentsBoards(),
        });
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

    ftxui::Component &GameDisplay::drawSpectate() {
        displayWindow_ = ftxui::Container::Horizontal({
                             leftPane(),
                             rightPane(),
                         })
                         | ftxui::center;

        return displayWindow_;
    }

    void GameDisplay::handleKeys() {
        displayWindow_ =
            ftxui::CatchEvent(displayWindow_, [&](ftxui::Event event) {
                if (event == ftxui::Event::Return) { // Keep Enter key for his
                                                     // original action
                    return false;
                }

                else if (event.is_mouse()) { // Do not handle mouse
                                             // events
                    return false;
                }

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
            });
    }

    ftxui::Component &GameDisplay::drawGameOver() {
        ftxui::Component title =
            ftxui::Renderer([] { return GAME_OVER_TITLE | ftxui::center; });

        ftxui::Component scoreText = ftxui::Renderer([&] {
            return ftxui::text("Your score was: "
                               + std::to_string(getSelfScore()))
                   | ftxui::center;
        });

        ftxui::Component button = ftxui::Button(
            std::string(STR_RETURN_TO_MAIN_MENU),
            [&] { mainTui_.stopRender(); }, GlobalButtonStyle());

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
            return ftxui::text("Your score was: "
                               + std::to_string(getSelfScore()))
                   | ftxui::center;
        });

        ftxui::Component button = ftxui::Button(
            std::string(STR_RETURN_TO_MAIN_MENU),
            [&] { mainTui_.stopRender(); }, GlobalButtonStyle());

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

        auto updateGame = [&] {
            gameContainer->DetachAllChildren();

            gameState_ = controller_.getGameState();

            if (std::visit(
                    [](const auto &gameState) { return gameState.isFinished; },
                    gameState_)) {
                if (isWinner()) {
                    gameContainer->Add(drawWin());
                } else {
                    gameContainer->Add(drawGameOver());
                }

                return;
            }

            std::visit(
                [&](const auto &gameState) {
                    using T = std::decay_t<decltype(gameState)>;
                    if constexpr (std::is_same_v<T, client::GameState>) {
                        if (getGameMode() == GameMode::Endless) {
                            drawEndlessMode();
                        } else {
                            drawMultiMode();
                        }

                        handleKeys();
                    } else if constexpr (std::is_same_v<
                                             T, client::GameStateViewer>) {
                        drawSpectate();
                    }
                },
                gameState_);

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

} // namespace TUI
