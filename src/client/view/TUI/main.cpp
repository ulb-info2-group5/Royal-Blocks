#include "screen_manager.hpp"
#include "game_display.hpp"
#include "../interfaceConfig.hpp"
#include "../dataExample.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

// int main() {
//     ScreenManager screenManager;
//     screenManager.run();
//     return 0;
// }

int main()
{
    // std::shared_ptr<ftxui::ScreenInteractive> screen = std::shared_ptr<ftxui::ScreenInteractive>(new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen()));
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();
    GameDisplay game = GameDisplay(std::make_shared<std::vector<std::vector<std::vector<colors>>>>(EXEMPLE_BOARDS), 
                    PlayMode::ROYAL, 9);
    
    game.drawWindow();
    screen.Loop(game.displayWindow_);
    return 0;
}