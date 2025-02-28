#include "game_display.hpp"

#include "../../../controller/controller.hpp"
#include "../game_menu/game_menu.hpp"

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp" // for Canvas
#include "ftxui/dom/node.hpp"   // for Render
#include "ftxui/screen/color.hpp" // for Color, Color::Red, Color::Blue, Color::Green, ftxui

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

ftxui::Color getFTXUIColor(colors color) {
    ftxui::Color returnValue = ftxui::Color::Blue;

    switch (color) {
    case BLACK:
        returnValue = ftxui::Color::Black;
        break;
    case WHITE:
        returnValue = ftxui::Color::White;
        break;
    case GREY:
        returnValue = ftxui::Color::Grey0;
        break;
    case DARK_BLUE:
        returnValue = ftxui::Color::Blue3;
        break;
    case LIGHT_BLUE:
        returnValue = ftxui::Color::Blue1;
        break;
    case PURPLE:
        returnValue = ftxui::Color::Purple3;
        break;
    case RED:
        returnValue = ftxui::Color::Red;
        break;
    case ORANGE:
        returnValue = ftxui::Color::Orange1;
        break;
    case PINK:
        returnValue = ftxui::Color::Pink1;
        break;
    case GREEN:
        returnValue = ftxui::Color::Green1;
        break;
    case YELLOW:
        returnValue = ftxui::Color::Yellow1;
        break;
    };

    return returnValue;
}

// constructor

GameDisplay::GameDisplay(
    std::shared_ptr<ftxui::ScreenInteractive> screen, Controller *controller,
    std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>
        boards,
    PlayMode play)
    : screen_{screen}, controller_(controller), playersBoards_{boards},
      play_{play} {
    // initialise for preview
    pseudos_ = {"juliette", "ethan", "quentin", "frog",   "lucas",
                "rafaou",   "jonas", "ernest",  "vanilla"};
    score_ = 10000;
    malusGauge_ = 0.5;
    energyGauge_ = 0.5;

    effects_ = {"bonus0", "bonus1", "bonus2", "bonus3", "bonus4",
                "bonus5", "bonus6", "bonus7", "bonus8"};
}

// protected methods

void GameDisplay::drawPlayerInfo() {
    playerInfo_ = ftxui::Renderer([&] {
        return ftxui::vbox({ftxui::text(std::to_string(score_)),
                            ftxui::text(pseudos_.at(0))})
               | ftxui::borderDashed;
    });
}

void GameDisplay::drawRoyalEffectsEnergy() {
    ftxui::Components effectsButton = {};

    for (uint8_t i = 0; i < 3; ++i) {
        ftxui::Component but = ftxui::Container::Horizontal({
            ftxui::Button(
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
            {ftxui::gaugeRight(energyGauge_),
             ftxui::text("energy power") | ftxui::borderRounded});
    });
}

void GameDisplay::displayLeftWindow() {
    ftxui::Component menuDisplay = ftxui::Button(
        "Quit Game", [&] { screen_->ExitLoopClosure()(); },
        ftxui::ButtonOption::Animated(ftxui::Color::Grey0));

    if (play_ == PlayMode::ROYAL) {
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

        for (uint32_t x = 0; x < WIDTH; ++x) {
            for (uint32_t y = 0; y < HEIGHT; ++y) {
                pixel.background_color =
                    getFTXUIColor(playersBoards_->at(0).at(y).at(x));

                for (uint32_t i = 0; i < LENGTH_PLAYER; ++i) {
                    playerCanvas.DrawBlockCircleFilled(
                        x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i,
                        LENGTH_PLAYER, pixel.background_color);
                }
            }
        }

        return ftxui::canvas(playerCanvas) | ftxui::border;
    });
}

void GameDisplay::displayMiddleWindow() {
    drawPlayerBoard();

    // need to modify this for different game mode
    ftxui::Component modeDisplay = ftxui::Renderer(
        [&] { return ftxui::text("Royal") | ftxui::borderRounded; });

    ftxui::Component playButtonsDisplay = ftxui::Container::Horizontal({
        ftxui::Button(
            "g", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
        ftxui::Button(
            "f", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
        ftxui::Button(
            "<-", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
        ftxui::Button(
            "->", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
        ftxui::Button(
            "j", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
        ftxui::Button(
            "G", [&] { /* function to call */ },
            ftxui::ButtonOption::Animated(ftxui::Color::Red))
            | ftxui::borderDouble,
    });

    displayMiddle_ = ftxui::Container::Vertical({
        modeDisplay,
        playerBoard_,
        playButtonsDisplay,
    });
}

void GameDisplay::drawOpponentsBoard() {
    opBoards_ = {};
    ftxui::Component opDisplay;

    for (uint32_t index = 1; index < playersBoards_->size(); ++index) {
        ftxui::Component opBoardDisplay = ftxui::Renderer([&](uint32_t index) {
            ftxui::Canvas opCanvas =
                ftxui::Canvas(WIDTH_OP_CANVAS, HEIGHT_OP_CANVAS);

            for (uint32_t x = 0; x < WIDTH; ++x) {
                for (uint32_t y = 0; y < HEIGHT; ++y) {

                    for (uint32_t i = 0; i < LENGTH_OPPONENT; ++i) {
                        opCanvas.DrawBlock(
                            x * LENGTH_OPPONENT + i, y * LENGTH_OPPONENT + i,
                            true,
                            getFTXUIColor(
                                playersBoards_->at(index).at(y).at(x)));
                    }
                }
            }

            return ftxui::canvas(opCanvas) | ftxui::border;
        });

        opDisplay = ftxui::Container::Vertical({
            opBoardDisplay,
            ftxui::Button(
                pseudos_.at(index), [&] { /* function to call */ },
                ftxui::ButtonOption::Animated(ftxui::Color::Yellow1))
                | ftxui::borderDouble,
        });

        opBoards_.push_back(opDisplay);
    }
}

void GameDisplay::displayOppponentsBoard() {
    drawOpponentsBoard();

    ftxui::Components rows = {};
    uint32_t totalPlayers = playersBoards_->size();

    for (uint32_t i = 0; i < 3; ++i) {
        ftxui::Component line;
        uint32_t leftPlayers = totalPlayers - (i * 3 + 1);

        if (leftPlayers <= 0) break;

        switch (leftPlayers) {
        case 1:
            line = ftxui::Container::Horizontal({opBoards_.at(0 + i * 3)});
            break;
        case 2:
            line = ftxui::Container::Horizontal(
                {opBoards_.at(0 + i * 3), opBoards_.at(1 + i * 3)});
            break;
        default:
            line = ftxui::Container::Horizontal({opBoards_.at(0 + i * 3),
                                                 opBoards_.at(1 + i * 3),
                                                 opBoards_.at(2 + i * 3)});
            break;
        }

        rows.push_back(line);
    }

    switch (rows.size()) {
    case 1:
        opBoardDisplay_ = ftxui::Container::Vertical({rows.at(0)});
        break;
    case 2:
        opBoardDisplay_ = ftxui::Container::Vertical({rows.at(0), rows.at(1)});
        break;
    case 3:
        opBoardDisplay_ =
            ftxui::Container::Vertical({rows.at(0), rows.at(1), rows.at(2)});
        break;
    }
}

void GameDisplay::displayOpponentBoardDuel() {
    opBoardDisplay_ = ftxui::Renderer([&] {
        ftxui::Canvas playerCanvas =
            ftxui::Canvas(WIDTH_PLAYER_CANVAS, HEIGHT_PLAYER_CANVAS);
        ftxui::Pixel pixel = ftxui::Pixel();

        for (uint32_t x = 0; x < WIDTH; ++x) {
            for (uint32_t y = 0; y < HEIGHT; ++y) {
                pixel.background_color =
                    getFTXUIColor(playersBoards_->at(1).at(y).at(x));

                for (uint32_t i = 0; i < LENGTH_PLAYER; ++i) {
                    playerCanvas.DrawBlockCircleFilled(
                        x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i,
                        LENGTH_PLAYER, pixel.background_color);
                }
            }
        }

        return ftxui::vbox({
            ftxui::canvas(playerCanvas) | ftxui::border,
            ftxui::text(pseudos_.at(1)) | ftxui::borderDouble,
        });
    });
}

void GameDisplay::displayMultiRightWindow() {
    if (play_ == PlayMode::DUEL) displayOpponentBoardDuel();
    else displayOppponentsBoard();

    ftxui::Component malusDisplay = ftxui::Renderer([&] {
        return ftxui::vbox({
            ftxui::gaugeRight(malusGauge_),
            ftxui::text("malus to come") | ftxui::borderDashed,
        });
    });

    displayRight_ = ftxui::Container::Vertical({
        malusDisplay,
        opBoardDisplay_,
    });
}

void GameDisplay::drawEndlessMode() {
    displayLeftWindow();
    displayMiddleWindow();

    displayWindow_ = ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
    });
}

void GameDisplay::drawMultiMode() {
    displayLeftWindow();
    displayMiddleWindow();
    displayMultiRightWindow();

    displayWindow_ = ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
        displayRight_,
    });
}

// public methods

void GameDisplay::render() {
    if (play_ == PlayMode::ENDLESS) drawEndlessMode();
    else drawMultiMode();

    screen_->Loop(displayWindow_);
}