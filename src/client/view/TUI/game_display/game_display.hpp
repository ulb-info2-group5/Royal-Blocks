#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../interfaceConfig.hpp"
#include "../../IGame.hpp"
#include "../../dataExample.hpp"

#include "ftxui/dom/canvas.hpp"  // for Canvas
#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_base.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <memory>
#include <utility>
#include <string>

const uint32_t PIXEL_LENGTH_PLAYER = 4,
               PIXEL_LENGTH_OPPONENT = 2;

const uint32_t WIDTH_PLAYER_CANVAS = 40,
               HEIGHT_PLAYER_CANVAS = 80,
               WIDTH_OP_CANVAS = 20,
               HEIGHT_OP_CANVAS = 40;


ftxui::Color getFTXUIColor(colors color);

class GameDisplay : public IGame 
{
    private:
        // std::shared_ptr<GameState> partyInfo_;
        // std::shared_ptr<PlayerState> player_;
        std::shared_ptr<ftxui::ScreenInteractive> screen_;
        std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> vectorBoards_;
        PlayMode playMode_;
        uint8_t totalPlayers_;
        uint32_t score_;
        std::vector<std::string> effects_ = {};

        ftxui::Component playerBoard_;
        ftxui::Components opBoards_;
        ftxui::Pixel pixel_;
        
        ftxui::Component displayRightSide_;
        ftxui::Component displayMiddleSide_;
        ftxui::Component displayLeftSide_;

    protected:

        void drawPlayerBoard() override;

        void drawOpponentsBoard() override;

        void displayBoardsOp();

        void displayRightSide();

        void displayMiddleSide();

        void displayLeftSide();

        //void drawEndlessMode() override;

        //void drawDualMode() override;

        //void drawClassicMode() override;

        void drawRoyalMode() override;

    public: 
        ftxui::Component displayWindow_;

        // std::shared_ptr<ftxui::ScreenInteractive> screen_;
        // ftxui::ScreenInteractive screen_;
        //GameDisplay(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<GameState> partyInfo_, std::shared_ptr<PlayerState> player_;);
        // GameDisplay(std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> boards, 
        //             PlayMode playMode, uint8_t numberPlayers, 
        //             std::shared_ptr<ftxui::ScreenInteractive> screen);
        
        GameDisplay(std::shared_ptr<ftxui::ScreenInteractive> &screen, std::shared_ptr<std::vector<std::vector<std::vector<colors>>>> boards, 
                    PlayMode playMode, uint8_t numberPlayers);


        ~GameDisplay() = default;


        void drawWindow() override;

        void render();
};

#endif