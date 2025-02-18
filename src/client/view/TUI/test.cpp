// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <stdio.h>                 // for getchar
#include <string>
#include <utility>
#include <ftxui/dom/elements.hpp>  // for Fit, canvas, operator|, border, Element
#include <ftxui/screen/screen.hpp>  // for Pixel, Screen
#include <ftxui/component/component.hpp>
#include <vector>                   // for vector, allocator
#include <memory>

#include "ftxui/dom/canvas.hpp"  // for Canvas
#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_base.hpp"
// #include "../../../../lib/grid-container.hpp"

//#include "game_display.hpp"
#include "../dataExample.hpp"
#include "../interfaceConstants.hpp"
#include "../IGame.hpp"

const uint32_t PIXEL_LENGTH_PLAYER = 4, PIXEL_LENGTH_OPPONENT = 2;

const uint32_t WIDTH_PLAYER_CANVAS = 40,
               HEIGHT_PLAYER_CANVAS = 80,
               WIDTH_OP_CANVAS = 20,
               HEIGHT_OP_CANVAS = 40;

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

// class Bitch
// {
//     private:
//     // ftxui::ScreenInteractive screen_;

//     protected:
//     void createDisplay();
    
//     public:
//     ftxui::Component doc_;
//     Bitch();
//     ~Bitch() = default;

//     void drawWindow();
// };

// void Bitch::createDisplay()
// {
//     ftxui::Component comp1 = ftxui::Renderer([&]{
//         return ftxui::text("hello") | ftxui::borderRounded;
//     }),
//     comp2 = ftxui::Renderer([&]{
//         return ftxui::text("coucou") | ftxui::borderDashed;
//     });

//     doc_ = ftxui::Container::Horizontal({
//         comp1,
//         comp2
//     });
// }

// Bitch::Bitch()
// {
//     doc_ = ftxui::Component();
//     // screen_ = ftxui::ScreenInteractive::TerminalOutput();
// }

// void Bitch::drawWindow()
// {
//     createDisplay();
//     // screen_.Loop(doc_);
// }

class GameDisplay : public IGame 
{
    private:
        // std::shared_ptr<GameState> partyInfo_;
        // std::shared_ptr<PlayerState> player_;
        

    protected:




        //void drawEndlessMode() override;

        //void drawDualMode() override;

        //void drawClassicMode() override;


    public: 
        std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> vectorBoards_;
        PlayMode playMode_;
        uint8_t totalPlayers_;
        uint32_t score_;
        std::vector<std::string> effects_ = {};

        ftxui::Components opBoards_;
        ftxui::Pixel pixel_;
        void drawRoyalMode() override;
        void drawOpponentsBoard() override;

        void displayBoardsOp();
        ftxui::Component playerBoard_;
        void drawPlayerBoard() override;
        void displayRightSide();

        void displayMiddleSide();

        void displayLeftSide();
        // ftxui::Component displayWindow_;
        ftxui::Component displayRightSide_;
        ftxui::Component displayMiddleSide_;
        ftxui::Component displayLeftSide_;

        // std::shared_ptr<ftxui::ScreenInteractive> screen_;
        // ftxui::ScreenInteractive screen_;
        //GameDisplay(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<GameState> partyInfo_, std::shared_ptr<PlayerState> player_;);
        // GameDisplay(std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> boards, 
        //             PlayMode playMode, uint8_t numberPlayers, 
        //             std::shared_ptr<ftxui::ScreenInteractive> screen);
        
        GameDisplay(std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> boards, 
                    PlayMode playMode, uint8_t numberPlayers);


        ~GameDisplay() = default;


        void drawWindow() override;
};

GameDisplay::GameDisplay(std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> boards, 
                        PlayMode playMode, uint8_t numberPlayers) : 
                        vectorBoards_{boards},
                        playMode_{playMode},
                        totalPlayers_{numberPlayers}
{
    //initialialising for the preview
    score_ = 100000;

    displayLeftSide_ = {};
    displayMiddleSide_ = {};
    displayRightSide_ = {};

    // displayWindow_ = ftxui::Component();

    pixel_ = ftxui::Pixel();

    // screen_ = ftxui::ScreenInteractive::FitComponent();

    // drawPlayerBoard();
    // if (playMode_ != PlayMode::ENDLESS) 
    // {
    //     drawOpponentsBoard();
    // } else 
    // {
    //     opBoards_ = {};
    // }

    if (playMode_ == PlayMode::ROYAL) 
    {
        effects_ = {"bon1", "bon2", "bon3", "bon4", "bon5", "bon6",
                    "bon7", "bon8", "bon9"};
    }

}

//GameDisplay::GameDisplay(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<GameState> partyInfo_, std::shared_ptr<PlayerState> player_;);


// protected methods

void GameDisplay::drawPlayerBoard()
{

    playerBoard_ = ftxui::Renderer([&] {

        ftxui::Canvas playerCanvas = ftxui::Canvas(WIDTH_PLAYER_CANVAS, HEIGHT_PLAYER_CANVAS);

        for (uint32_t y = 0; y < HEIGHT; ++y) 
        {
            for (uint32_t x = 0; x < WIDTH; ++x)
            {
                pixel_.background_color = getFTXUIColor(vectorBoards_->at(0).at(y).at(x));
                
                //for thickness of the pixel
                for (uint32_t i = 0; i < PIXEL_LENGTH_PLAYER; ++i)
                {
                    playerCanvas.DrawPixel(x * PIXEL_LENGTH_PLAYER + i, y * PIXEL_LENGTH_PLAYER + i, pixel_);
                }
            }
        }

        return ftxui::canvas(std::move(playerCanvas)) | ftxui::border;
    });

}

void GameDisplay::drawOpponentsBoard()
{

    for (uint32_t index = 1; index < vectorBoards_->size() ; ++index)
    {
        ftxui::Component boardPlayer = ftxui::Renderer([&] {
        
        ftxui::Canvas opCanvas = ftxui::Canvas(WIDTH_OP_CANVAS, HEIGHT_OP_CANVAS);

        for (uint32_t y = 0; y < HEIGHT; ++y) 
        {
            for (uint32_t x = 0; x < WIDTH; ++x)
            {
                pixel_.background_color = getFTXUIColor((*vectorBoards_).at(index).at(y).at(x));
                
                //for thickness of the pixel
                for (uint32_t i = 0; i < PIXEL_LENGTH_OPPONENT; ++i)
                {
                    opCanvas.DrawPixel(x * PIXEL_LENGTH_OPPONENT + i, y * PIXEL_LENGTH_OPPONENT + i, pixel_);
                }
            }
        }

        return ftxui::canvas(std::move(opCanvas)) | ftxui::border;
    });

    
    if (opBoards_.size() == totalPlayers_ - 1) opBoards_.at(index) = boardPlayer;
    else opBoards_.push_back(boardPlayer);

    }

    
}

void GameDisplay::displayBoardsOp() 
{
    ftxui::Components rows;
    //yeah i need to do this because idk how to use an extern ftxui lib and i can't use gridbox bc typo
    for (uint8_t i = 0; i < 3; ++i)
    {
        ftxui::Component line;

        // need to verify if the opponents grid to add is still in the totalPlayers' number range
        // -1 to substract the main player
        if (totalPlayers_ - ( 1 + i * 3) <= 0) break;

        //switch case to make a line 3 x 1
        switch (totalPlayers_ - ( 1 + i * 3))
        {
            case 1 : 
                line = ftxui::Container::Horizontal({opBoards_.at(0 + i * 3)});
                break;
            case 2 : 
                line = ftxui::Container::Horizontal({opBoards_.at(0 + i * 3), opBoards_.at(1 + i * 3)});
                break;
            default : 
                line = ftxui::Container::Horizontal({opBoards_.at(0 + i * 3), opBoards_.at(1 + i * 3), opBoards_.at(2 + i * 3)});
                break;
        }

        rows.push_back(line);
    }

    // switch case to make a grid like 3 x 3
    switch(rows.size())
    {
        case 1 : displayRightSide_ = ftxui::Container::Vertical({rows.at(0)}); break;
        case 2 : displayRightSide_ = ftxui::Container::Vertical({rows.at(0), rows.at(1)}); break;
        case 3 : displayRightSide_ = ftxui::Container::Vertical({rows.at(0), rows.at(1), rows.at(2)}); break;
    };

}

void GameDisplay::displayRightSide() 
{
    drawOpponentsBoard();
    displayBoardsOp();
} 

void GameDisplay::displayMiddleSide()
{
    drawPlayerBoard();

    // //to suppress later this part of code
    // std::string test;

    // switch(playMode_)
    // {
    //     case PlayMode::ENDLESS : test = "Endless"; break;
    //     case PlayMode::DUEL : test = "Duel" ; break;
    //     case PlayMode::CLASSIC : test = "Classic" ; break;
    //     case PlayMode::ROYAL : test = "Royal"; break;
    // };

    ftxui::Component mode = ftxui::Renderer([&]{
        return ftxui::text("royal") | ftxui::borderRounded;
    });

    ftxui::Component score = ftxui::Renderer([&]{
        return ftxui::text(std::to_string(score_)) | ftxui::borderRounded;
    });

    displayMiddleSide_ = ftxui::Container::Vertical({
        mode,
        playerBoard_,
        score,
    });

}

void GameDisplay::displayLeftSide()
{
    ftxui::Components lines;

    for (uint8_t i = 0; i < 3; ++i)
    {
        ftxui::Component line = ftxui::Container::Horizontal({
            ftxui::Button(
                effects_.at(i), [&] {/*function void to call*/}, ftxui::ButtonOption::Animated(ftxui::Color::Red)
            ),
            ftxui::Button(
                effects_.at(i + 1), [&] {/*function void to call*/}, ftxui::ButtonOption::Animated(ftxui::Color::Red)
            ),
            ftxui::Button(
                effects_.at(i + 2), [&] {/*function void to call*/}, ftxui::ButtonOption::Animated(ftxui::Color::Red)
            )
        });

        lines.push_back(line);
    }

    displayLeftSide_ = ftxui::Container::Vertical({
        lines.at(0),
        lines.at(1),
        lines.at(2)
    });

}
//void GameDisplay::drawEndlessMode() override;

//void GameDisplay::drawDualMode() override;

//void GameDisplay::drawClassicMode() override;

void GameDisplay::drawRoyalMode() 
{
    // displayLeftSide();
    // displayMiddleSide();
    // displayRightSide();

    // displayWindow_ = ftxui::Container::Horizontal({
    //     displayLeftSide_,
    //     displayMiddleSide_,
    //     displayRightSide_,
    // });
}


// public methods 

void GameDisplay::drawWindow() 
{
    // switch (playMode_)
    // {
    //     case PlayMode::ENDLESS : break;
    //     case PlayMode::DUEL : break;
    //     case PlayMode::CLASSIC : break;
    //     case PlayMode::ROYAL : drawRoyalMode(); break;
    // };
    // drawRoyalMode();

    // screen_->Loop(displayWindow_);
    displayLeftSide();
    displayMiddleSide();
    displayRightSide();

    // displayWindow_ = ftxui::Container::Horizontal({
    //     displayLeftSide_,
    //     displayMiddleSide_,
    //     displayRightSide_,
    // });
}


int main()
{   
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();
    GameDisplay game = GameDisplay(std::make_shared<std::vector<std::vector<std::vector<colors>>>>(EXEMPLE_BOARDS), 
                    PlayMode::ROYAL, 9);

    // game.displayRightSide();
    // game.displayLeftSide();
    // game.displayMiddleSide();
    // game.drawPlayerBoard();
    game.drawWindow();
    //il aime pas ce container doc
    ftxui::Component doc = ftxui::Container::Horizontal({
        game.displayLeftSide_,
        game.displayMiddleSide_,
        game.displayRightSide_
    });

    screen.Loop(doc);
    return 0;
}