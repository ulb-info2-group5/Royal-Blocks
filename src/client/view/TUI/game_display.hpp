#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../interfaceConfig.hpp"
#include "../IGame.hpp"
#include "menu_ui.hpp"
#include "screen_manager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <memory>

const uint32_t PIXEL_SIDE = 20;

ftxui::Color getFTXUIColor(colors color);

class GameDisplay : public IGame 
{
    private:
       // std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>,HEIGHT>>> boards_;
        std::shared_ptr<ScreenManager> screenManager_;
        ftxui::Canvas canvas_ = ftxui::Canvas(100,100);
    
    public: 
        //GameDisplay(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>,HEIGHT>>> boards);
         GameDisplay(std::shared_ptr<ScreenManager> screenManager);
        ~GameDisplay() = default;

        void drawPlayerBoard() override;

        //void drawOpponentsBoard() override;

        void drawWindow() override;
};

#endif