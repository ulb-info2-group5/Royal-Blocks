#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../interfaceConfig.hpp"
#include "../IGame.hpp"
#include "menu_ui.hpp"
#include "screen_manager.hpp"

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


ftxui::Color getFTXUIColor(colors color);

class GameDisplay : public IGame 
{
    private:
        PlayMode playMode_;

        ftxui::Canvas playerCanvas_;
        std::vector<ftxui::Canvas> opponentsCanvas_;
        ftxui::Pixel pixel_;

        ftxui::Components displayRightSide_;
        ftxui::Components displayMiddleSide_;
        ftxui::Components displayLeftSide_;
        ftxui::Component displayWindow_;

        std::shared_ptr<ftxui::ScreenInteractive> screen_;

    protected:

        void drawEndlessMode();

        void drawDualMode();

        void drawClassicMode();

        void drawRoyalMode();

    public: 
        //GameDisplay(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>,HEIGHT>>> boards);
         GameDisplay(std::shared_ptr<ScreenManager> screenManager);
        ~GameDisplay() = default;

        void drawPlayerBoard() override;

        //void drawOpponentsBoard() override;

        void drawWindow() override;
};

#endif