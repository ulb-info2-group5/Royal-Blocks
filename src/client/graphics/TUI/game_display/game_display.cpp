#include "game_display.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include "../../../core/controller/controller.hpp"
#include "board/board.hpp"
#include "../../color.hpp"

// TODO: this should defo go somewhere else
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/pixel.hpp>
#include <optional>
#include <stdexcept>
#include <string>

Color colorIdToColor(unsigned colorID) {
    // TODO: add missing colorID's such as mini tetromino
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
    case PENALTY_BLOCKS_COLOR_ID:
        return Color::Grey;
    default:
        throw std::runtime_error{"unknown color"};
    };
}

ftxui::Color getFTXUIColor(Color color, Controller::SelfCellType selfCellType =
                                            Controller::SelfCellType::Placed) {
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

    if (selfCellType == Controller::SelfCellType::Preview) {
        returnValue =
            ftxui::Color::Blend(returnValue, ftxui::Color::RGB(128, 128, 128));
    }

    return returnValue;
}

// constructor

GameDisplay::GameDisplay(ScreenManager &screenManager, Controller &controller)
    : screenManager_(screenManager), controller_(controller) {
    // initialise for preview
    // penaltyGauge_ = 0.5;

    effects_ = {"bonus0", "bonus1", "bonus2", "bonus3", "bonus4",
                "bonus5", "bonus6", "bonus7", "bonus8"};
}

// protected methods

void GameDisplay::drawPlayerInfo() {
    playerInfo_ = ftxui::Renderer([&] {
        return ftxui::vbox(

                   {ftxui::text(std::to_string(controller_.getSelfScore())),
                    // TODO: use the actual nickname
                    ftxui::text(controller_.getSelfUsername())})
               | ftxui::borderDashed;
    });
}

void GameDisplay::drawRoyalEffectsEnergy() {
    ftxui::Components effectsButton = {};

    for (uint8_t i = 0; i < 3; ++i) {
        ftxui::Component but = ftxui::Container::Horizontal({
            ftxui::Button(
                // TODO: use the effects
                effects_.at(i * 3), [&] { /* function to call */ },
                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
            ftxui::Button(
                effects_.at(i * 3 + 1), [&] { /* function to call */ },
                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
            ftxui::Button(
                effects_.at(i * 3 + 2), [&] { /* function to call */ },
                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
        });

        effectsButton.push_back(but);
    }

    ftxui::Component effectsDisplay = ftxui::Container::Vertical(
        {effectsButton.at(0), effectsButton.at(1), effectsButton.at(2)});

    effectsDisplay_ = ftxui::Renderer([&] {
        return ftxui::vbox(
            {ftxui::gaugeRight(
                 // TODO: check that whether this must be below 1.
                 controller_.getSelfEnergy()),
             ftxui::text("energy power") | ftxui::borderRounded});
    });
}

void GameDisplay::displayLeftWindow() {
    ftxui::Component menuDisplay = ftxui::Button(
        std::string(STR_QUIT_GAME), [&] { screenManager_.stopRender(); },
        GlobalButtonStyle());

    if (controller_.getGameMode() == GameMode::RoyalCompetition) {
        drawPlayerInfo();
        drawRoyalEffectsEnergy();

        displayLeft_ = ftxui::Container::Vertical({
            menuDisplay,
            effectsDisplay_,
            playerInfo_,
        });
    } else {
        drawPlayerInfo();

        displayLeft_ = ftxui::Container::Vertical({
            menuDisplay,
            playerInfo_,
        });
    }
}

void GameDisplay::drawPlayerBoard() {
    playerBoard_ = ftxui::Renderer([&] {
        ftxui::Canvas playerCanvas =
            ftxui::Canvas(WIDTH_PLAYER_CANVAS, HEIGHT_PLAYER_CANVAS);
        ftxui::Pixel pixel = ftxui::Pixel();

        size_t height = controller_.getBoardHeight();
        size_t width = controller_.getBoardWidth();

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {

                pixel.background_color =
                    controller_.selfCellInfoAt(x, y)
                        .transform([](auto cellInfo) {
                            return getFTXUIColor(colorIdToColor(cellInfo.first),
                                                 cellInfo.second);
                        })
                        .value_or(getFTXUIColor(Color::Black));

                for (uint32_t dy = 0; dy < CELL_SIZE_PLAYER; ++dy) {
                    for (uint32_t dx = 0; dx < CELL_SIZE_PLAYER; ++dx) {
                        playerCanvas.DrawBlock(
                            x * CELL_SIZE_PLAYER + dx,
                            (height - 1 - y) * CELL_SIZE_PLAYER + dy, true,
                            pixel.background_color);
                    }
                }
            }
        }

        return ftxui::canvas(playerCanvas) | ftxui::border | ftxui::center;
    });
}

void GameDisplay::displayMiddleWindow() {
    drawPlayerBoard();

    ftxui::Component modeDisplay = ftxui::Renderer([&] {
        return ftxui::text(toString(controller_.getGameMode())) | ftxui::center
               | ftxui::border;
    });

    displayMiddle_ = ftxui::Container::Vertical({
        modeDisplay
            | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, WIDTH_PLAYER_CANVAS / 2)
            | ftxui::center,
        playerBoard_,
    });
}

void GameDisplay::drawOpponentsBoard() {
    opBoards_.clear();
    for (uint32_t index = 0; index < controller_.getNumOpponents(); ++index) {
        ftxui::Component opBoardDisplay = ftxui::Renderer([&, index] {
            ftxui::Canvas opCanvas =
                ftxui::Canvas(WIDTH_OP_CANVAS, HEIGHT_OP_CANVAS);
            ftxui::Pixel pixel = ftxui::Pixel();

            size_t height = controller_.getBoardHeight();
            size_t width = controller_.getBoardWidth();

            for (uint32_t y = 0; y < height; ++y) {
                for (uint32_t x = 0; x < width; ++x) {

                    pixel.background_color = getFTXUIColor(
                        controller_.opponentsBoardGetColorIdAt(index, x, y)
                            .transform(
                                [](auto id) { return colorIdToColor(id); })
                            .value_or(Color::Black));

                    for (uint32_t dy = 0; dy < CELL_SIZE_OPPONENT; ++dy) {
                        for (uint32_t dx = 0; dx < CELL_SIZE_OPPONENT; ++dx) {
                            opCanvas.DrawBlock(
                                x * CELL_SIZE_OPPONENT + dx,
                                (height - 1 - y) * CELL_SIZE_OPPONENT + dy,
                                true, pixel.background_color);
                        }
                    }
                }
            }

            return ftxui::canvas(opCanvas) | ftxui::border;
        });

        ftxui::Component opDisplay = ftxui::Container::Vertical({
            opBoardDisplay,
            ftxui::Button(
                controller_.getOpponentUsername(index),
                [&] { /* function to call */ },
                ftxui::ButtonOption::Animated(ftxui::Color::Yellow1))
                | ftxui::borderDouble,
        });

        opBoards_.push_back(opDisplay);
    }
}

void GameDisplay::displayOppponentsBoard() {
    drawOpponentsBoard();

    ftxui::Components rows = {};
    uint32_t totalOpponentsPlayers = controller_.getNumOpponents();

    for (uint32_t i = 0; i < 2; ++i) { // 2 rows
        ftxui::Component line;
        uint32_t leftPlayers = (totalOpponentsPlayers > i * 4)
                                   ? totalOpponentsPlayers - (i * 4)
                                   : 0; // 4 players per row max

        if (leftPlayers <= 0) {
            break;
        }

        std::vector<ftxui::Component> components;
        for (uint32_t j = 0;
             j < std::min(leftPlayers, 4u) && (i * 4 + j) < opBoards_.size();
             ++j) {
            components.push_back(opBoards_.at(i * 4 + j));
        }

        line = ftxui::Container::Horizontal(components);
        rows.push_back(line);
    }

    switch (rows.size()) {
    case 1:
        opBoardDisplay_ = ftxui::Container::Vertical({rows.at(0)});
        break;
    case 2:
        opBoardDisplay_ = ftxui::Container::Vertical({rows.at(0), rows.at(1)});
        break;
    }
}

void GameDisplay::displayOpponentBoardDuel() {
    opBoardDisplay_ = ftxui::Renderer([&] {
        ftxui::Canvas playerCanvas = ftxui::Canvas(
            WIDTH_PLAYER_CANVAS,
            HEIGHT_PLAYER_CANVAS); // For dual the size of the board is the same
                                   // as the player's
        ftxui::Pixel pixel = ftxui::Pixel();

        size_t height = controller_.getBoardHeight();
        size_t width = controller_.getBoardWidth();

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {

                pixel.background_color = getFTXUIColor(
                    controller_.opponentsBoardGetColorIdAt(0, x, y)
                        .transform([](auto id) { return colorIdToColor(id); })
                        .value_or(Color::Black));

                for (uint32_t dy = 0; dy < CELL_SIZE_PLAYER;
                     ++dy) { // For dual the size of the cells of the tetrominos
                             // is the same as the player's
                    for (uint32_t dx = 0; dx < CELL_SIZE_PLAYER;
                         ++dx) { // For dual the size of the cells of the
                                 // tetrominos is the same as the player's
                        playerCanvas.DrawBlock(
                            x * CELL_SIZE_PLAYER
                                + dx, // For dual the size of the cells of the
                                      // tetrominos is the same as the player's
                            (height - 1 - y) * CELL_SIZE_PLAYER + dy,
                            true, // For dual the size of the cells of the
                                  // tetrominos is the same as the player's
                            pixel.background_color);
                    }
                }
            }
        }

        return ftxui::vbox({
            ftxui::canvas(playerCanvas) | ftxui::border,
            ftxui::text(controller_.getOpponentUsername(0))
                | ftxui::borderDouble,
        });
    });
}

void GameDisplay::displayMultiRightWindow() {
    if (controller_.getGameMode() == GameMode::Dual) {
        displayOpponentBoardDuel();
    } else {
        displayOppponentsBoard();
    }

    // ftxui::Component penaltyDisplay = ftxui::Renderer([&] {
    //     return ftxui::vbox({
    //         ftxui::gaugeRight(penaltyGauge_),
    //         ftxui::text("penalty to come") | ftxui::borderDashed,
    //     });
    // });

    displayRight_ = ftxui::Container::Vertical({
        // penaltyDisplay,
        opBoardDisplay_,
    });
}

void GameDisplay::drawEndlessMode() {
    displayLeftWindow();
    displayMiddleWindow();

    displayWindow_ = ftxui::Container::Horizontal({
                         displayLeft_,
                         displayMiddle_,
                     })
                     | ftxui::center;
}

void GameDisplay::drawMultiMode() {
    displayLeftWindow();
    displayMiddleWindow();
    displayMultiRightWindow();

    displayWindow_ = ftxui::Container::Horizontal({
                         displayLeft_,
                         displayMiddle_,
                         displayRight_,
                     })
                     | ftxui::center;
}

void GameDisplay::handleKeys() {
    displayWindow_ = ftxui::CatchEvent(displayWindow_, [&](ftxui::Event event) {
        if (event == ftxui::Event::Return) { // Keep Enter key for
                                             // his original action
            return false;
        }

        else if (event.is_mouse()) { // Do not handle mouse events
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

void GameDisplay::updateDisplay() {
    if (controller_.getGameMode() == GameMode::Endless) {
        drawEndlessMode();
    } else {
        drawMultiMode();
    }
}

// public methods

void GameDisplay::render() {
    ftxui::Component gameContainer = ftxui::Container::Vertical({});

    auto updateGameDisplay = [&] {
        if (controller_.noGame()) {
            screenManager_.stopRender();
            return;
        }
        gameContainer->DetachAllChildren();
        updateDisplay();
        handleKeys();
        gameContainer->Add(displayWindow_);
    };

    ftxui::Component render =
        ftxui::Renderer(ftxui::Container::Vertical({ftxui::Container::Vertical({
                            gameContainer,
                        })}),
                        [&] {
                            updateGameDisplay();
                            return ftxui::vbox({
                                       gameContainer->Render(),
                                   })
                                   | ftxui::borderHeavy | ftxui::center;
                        });

    screenManager_.render(render);
    std::cerr << "after game display" << std::endl;
}
