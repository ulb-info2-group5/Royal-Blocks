#include "screen_manager.hpp"
// #include "game_display.hpp"
// #include "../interfaceConfig.hpp"
// #include "../dataExample.hpp"

int main() {
    ScreenManager screenManager;
    screenManager.run();
    return 0;
}

// int main()
// {
//     ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();

//     GameDisplay game = GameDisplay(std::make_shared<std::vector<std::vector<std::vector<colors>>>>(EXEMPLE_BOARDS), 
//                     PlayMode::ROYAL, 9, 
//                     screen);
    
//     game.drawWindow();
//     return 0;
// }