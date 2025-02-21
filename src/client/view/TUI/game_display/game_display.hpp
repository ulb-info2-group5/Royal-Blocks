#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../interfaceConstants.hpp"
// #include "../../IGame.hpp"
#include "../../dataExample.hpp"

#include "ftxui/dom/canvas.hpp"  // for Canvas
#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_base.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <array>

const uint32_t LENGTH_PLAYER = 4,
               LENGTH_OPPONENT = 2, 
               PADDING = 10;

const uint32_t WIDTH_PLAYER_CANVAS = 40,
               HEIGHT_PLAYER_CANVAS = 80,
               WIDTH_OP_CANVAS = 20,
               HEIGHT_OP_CANVAS = 40;

enum class PlayMode : uint8_t 
{
    ENDLESS,
    DUEL   ,
    CLASSIC,
    ROYAL
};


ftxui::Color getFTXUIColor(colors color);

class GameDisplay
{
    private:
    std::shared_ptr<ftxui::ScreenInteractive> screen_;

    std::vector<std::string> pseudos_;
    std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>> playersBoards_;
    uint32_t score_;
    float malusGauge_;
    PlayMode play_;

    float energyGauge_;
    std::vector<std::string> effects_ = {};

    ftxui::Component displayRight_;
    ftxui::Component displayMiddle_;
    ftxui::Component displayLeft_;
    ftxui::Component displayWindow_;

    protected:

    void drawDuoRight();

    void drawRoyalRight();

    void drawMiddle();

    void drawEndlessLeft();

    void drawRoyalLeft();

    void drawEndless();

    void drawDuo();

    void drawClassic();

    void drawRoyal();

    public:

    GameDisplay(std::shared_ptr<ftxui::ScreenInteractive> screen, std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>> boards,
                PlayMode play);

    void render();


};

#endif