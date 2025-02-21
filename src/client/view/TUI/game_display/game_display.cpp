#include "game_display.hpp"

#include "ftxui/dom/canvas.hpp"  // for Canvas
#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_base.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

ftxui::Color getFTXUIColor(colors color)
{
    ftxui::Color returnValue = ftxui::Color::Blue;

    switch(color)
    {
        case BLACK : returnValue = ftxui::Color::Black; break;
        case WHITE : returnValue = ftxui::Color::White; break;
        case GREY  : returnValue = ftxui::Color::Grey0; break;
        case DARK_BLUE : returnValue = ftxui::Color::Blue3; break;
        case LIGHT_BLUE : returnValue = ftxui::Color::Blue1; break;
        case PURPLE : returnValue = ftxui::Color::Purple3; break;
        case RED : returnValue = ftxui::Color::Red; break;
        case ORANGE : returnValue = ftxui::Color::Orange1; break;
        case PINK : returnValue = ftxui::Color::Pink1; break;
        case GREEN : returnValue = ftxui::Color::Green1; break;
        case YELLOW : returnValue = ftxui::Color::Yellow1; break;
    };

    return returnValue;
}

// constructor 

GameDisplay::GameDisplay(std::shared_ptr<ftxui::ScreenInteractive> screen, std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>> boards,
                PlayMode play) :
                screen_{screen}, playersBoards_{boards}, play_{play}
{
    // initialise for preview
    pseudos_ = {"juliette", "ethan", "quentin", "frog", 
             "lucas", "rafaou", "jonas", "ernest", "vanilla"};
    score_ = 10000;
    malusGauge_ = 0.5;
    energyGauge_ = 0.5;

    effects_ = {"bonus0","bonus1", "bonus2", "bonus3", 
                "bonus4", "bonus5", "bonus6", "bonus7", "bonus8"};

}


// protected methods

void GameDisplay::drawEndlessLeft()
{
    ftxui::Component menuDisplay = ftxui::Button("Quit Game", [&] { /* function to call */}, 
                                                ftxui::ButtonOption::Animated(ftxui::Color::Grey0));
    ftxui::Component playerDisplay = ftxui::Renderer([&]{
        return ftxui::vbox({
            ftxui::text(std::to_string(score_)),
            ftxui::text(pseudos_.at(0))
        }) | ftxui::borderDashed;
    });

    displayLeft_ = ftxui::Container::Vertical({
        menuDisplay,
        playerDisplay,
    });
}

void GameDisplay::drawRoyalLeft()
{
    ftxui::Component menuDisplay = ftxui::Button("Quit Game", [&] { /* function to call */}, 
                                                ftxui::ButtonOption::Animated(ftxui::Color::Grey0));
    
    ftxui::Components effectsButton = {};

    for (uint8_t i = 0; i < 3; ++i)
    {
        ftxui::Component but = ftxui::Container::Horizontal({
            ftxui::Button(effects_.at(i * 3 ), [&] { /* function to call */}, 
                                                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
            ftxui::Button(effects_.at(i * 3 + 1), [&] { /* function to call */}, 
                                                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
            ftxui::Button(effects_.at(i * 3 + 2 ), [&] { /* function to call */}, 
                                                ftxui::ButtonOption::Animated(ftxui::Color::Red)),
        });

        effectsButton.push_back(but);
    }

    ftxui::Component effectsDisplay = ftxui::Container::Vertical({
        effectsButton.at(0),
        effectsButton.at(1),
        effectsButton.at(2)
    });

    ftxui::Component energyDisplay = ftxui::Renderer([&]{
        return ftxui::vbox({
            ftxui::gaugeRight(energyGauge_),
            ftxui::text("energy power") | ftxui::borderRounded}); 
    });

    ftxui::Component playerDisplay = ftxui::Renderer([&]{
        return ftxui::vbox({
            ftxui::text(std::to_string(score_)),
            ftxui::text(pseudos_.at(0))
        }) | ftxui::borderDashed;
    });

    displayLeft_ = ftxui::Container::Vertical({
        menuDisplay,
        effectsDisplay,
        energyDisplay,
        playerDisplay,
    });
}

void GameDisplay::drawMiddle()
{
    ftxui::Component modeDisplay = ftxui::Renderer([&] {
        return ftxui::text("Royal") | ftxui::borderRounded;
    });

    ftxui::Component boardPlayerDisplay = ftxui::Renderer([&] {
        ftxui::Canvas playerCanvas = ftxui::Canvas(WIDTH_PLAYER_CANVAS, HEIGHT_PLAYER_CANVAS);
        ftxui::Pixel pixel = ftxui::Pixel();

        for (uint32_t x = 0; x < WIDTH; ++x)
        {
            for (uint32_t y = 0; y < HEIGHT; ++y)
            {
                pixel.background_color = getFTXUIColor(playersBoards_->at(0).at(y).at(x));

                for (uint32_t i = 0; i < LENGTH_PLAYER; ++i)
                {
                    // playerCanvas.DrawBlock(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, true, pixel.background_color);
                    // playerCanvas.DrawPoint(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, true, pixel.background_color);
                    // playerCanvas.DrawPointCircleFilled(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, LENGTH_PLAYER, pixel.background_color);
                    playerCanvas.DrawBlockCircleFilled(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, LENGTH_PLAYER, pixel.background_color);
                }
            }
        }

        return ftxui::canvas(playerCanvas) | ftxui::border;
    });

    ftxui::Component playButtonsDisplay = ftxui::Container::Horizontal({
        ftxui::Button("g", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
        ftxui::Button("f", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
        ftxui::Button("<-", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
        ftxui::Button("->", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
        ftxui::Button("j", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
        ftxui::Button("G", [&] { /* function to call */}, 
                    ftxui::ButtonOption::Animated(ftxui::Color::Red)) | ftxui::borderDouble,
    });

    displayMiddle_ = ftxui::Container::Vertical({
        modeDisplay,
        boardPlayerDisplay,
        playButtonsDisplay,
    });
}

void GameDisplay::drawDuoRight()
{
    ftxui::Component boardOpDisplay = ftxui::Renderer([&] {
        ftxui::Canvas playerCanvas = ftxui::Canvas(WIDTH_PLAYER_CANVAS, HEIGHT_PLAYER_CANVAS);
        ftxui::Pixel pixel = ftxui::Pixel();

        for (uint32_t x = 0; x < WIDTH; ++x)
        {
            for (uint32_t y = 0; y < HEIGHT; ++y)
            {
                pixel.background_color = getFTXUIColor(playersBoards_->at(1).at(y).at(x));

                for (uint32_t i = 0; i < LENGTH_PLAYER; ++i)
                {
                    // playerCanvas.DrawBlock(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, true, pixel.background_color);
                    // playerCanvas.DrawPoint(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, true, pixel.background_color);
                    // playerCanvas.DrawPointCircleFilled(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, LENGTH_PLAYER, pixel.background_color);
                    playerCanvas.DrawBlockCircleFilled(x * LENGTH_PLAYER + i, y * LENGTH_PLAYER + i, LENGTH_PLAYER, pixel.background_color);
                }
            }
        }

        return ftxui::vbox({
            ftxui::canvas(playerCanvas) | ftxui::border,
            ftxui::text(pseudos_.at(1)) | ftxui::borderDouble,
        });
    });

    ftxui::Component malusDisplay = ftxui::Renderer([&]{
         return ftxui::vbox({
            ftxui::gaugeRight(malusGauge_),
            ftxui::text("malus to come") | ftxui::borderDashed,
            });
    });

    displayRight_ = ftxui::Container::Vertical({
        malusDisplay,
        boardOpDisplay,
    });

}

void GameDisplay::drawRoyalRight()
{
    ftxui::Components boardsOp = {}, rows = {};
    ftxui::Component opDisplay;
    uint32_t totalPlayers = playersBoards_->size();

    uint32_t index;
    for (index = 1; index < totalPlayers; ++index)
    {
        ftxui::Component opBoardDisplay = ftxui::Renderer([&](uint32_t index) {
            ftxui::Canvas opCanvas = ftxui::Canvas(WIDTH_OP_CANVAS, HEIGHT_OP_CANVAS);

            for (uint32_t x = 0; x < WIDTH; ++x)
            {
                for (uint32_t y = 0; y < HEIGHT; ++y)
                {

                    for (uint32_t i = 0; i < LENGTH_OPPONENT; ++i)
                    {
                        opCanvas.DrawBlock(x * LENGTH_OPPONENT + i, y * LENGTH_OPPONENT + i, true, getFTXUIColor(playersBoards_->at(index).at(y).at(x)));
                    }
                }
            }

            return ftxui::canvas(opCanvas) | ftxui::border; 
        });

        opDisplay = ftxui::Container::Vertical({
            opBoardDisplay,
            ftxui::Button(pseudos_.at(index), [&] { /* function to call */}, 
                 ftxui::ButtonOption::Animated(ftxui::Color::Yellow1)) | ftxui::borderDouble,
        });

        boardsOp.push_back(opDisplay);
    }

    ftxui::Component malusDisplay = ftxui::Renderer([&]{
         return ftxui::vbox({
            ftxui::gaugeRight(malusGauge_),
            ftxui::text("malus to come") | ftxui::borderDashed,
            });
    });

    for (uint32_t i = 0; i < 3; ++i)
    {   
        ftxui::Component line;
        uint32_t leftPlayers = totalPlayers - (i*3 + 1);

        if (leftPlayers  <= 0) break;

        switch(leftPlayers)
        {
            case 1 :
            line = ftxui::Container::Horizontal({boardsOp.at(0 + i * 3)}); break;
            case 2 :
            line = ftxui::Container::Horizontal({boardsOp.at(0 + i * 3), boardsOp.at(1 + i * 3)}); break;
            default : 
            line = ftxui::Container::Horizontal({boardsOp.at(0 + i * 3), boardsOp.at(1 + i * 3), boardsOp.at(2 + i * 3)}); break;
        }

        rows.push_back(line); 
    }

    switch(rows.size())
    {
        case 1 : displayRight_ = ftxui::Container::Vertical({malusDisplay, rows.at(0)}); break;
        case 2 : displayRight_ = ftxui::Container::Vertical({malusDisplay, rows.at(0), rows.at(1)}); break;
        case 3 : displayRight_ = ftxui::Container::Vertical({malusDisplay, rows.at(0), rows.at(1), rows.at(2)}); break;
    }
}

void GameDisplay::drawEndless()
{
    drawEndlessLeft();
    drawMiddle();
    
    displayWindow_= ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
    });
}

void GameDisplay::drawDuo()
{
    drawEndlessLeft();
    drawMiddle();
    drawDuoRight();

    displayWindow_ = ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
        displayRight_,
    });
}

void GameDisplay::drawClassic()
{
    drawEndlessLeft();
    drawMiddle();
    drawRoyalRight();

    displayWindow_ = ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
        displayRight_,
    });
}

void GameDisplay::drawRoyal()
{
    drawRoyalLeft();
    drawMiddle();
    drawRoyalRight();

    displayWindow_ = ftxui::Container::Horizontal({
        displayLeft_,
        displayMiddle_,
        displayRight_,
    });
}


// public methods

void GameDisplay::render()
{
    switch(play_)
    {
        case PlayMode::ENDLESS: break;
        case PlayMode::DUEL: break;
        case PlayMode::CLASSIC: break;
        case PlayMode::ROYAL: drawRoyal(); break;
    };

    screen_->Loop(displayWindow_);
}