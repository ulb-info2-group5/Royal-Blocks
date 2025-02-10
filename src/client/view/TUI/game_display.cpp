#include "game_display.hpp"

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

GameDisplay::GameDisplay(std::shared_ptr<ScreenManager> screenManager,
                        std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>,HEIGHT>>> boards) : 
                        screenManager_{screenManager}, boards_{boards} {}

void GameDisplay::drawPlayerBoard() override
{
    // auto c = ftxui::Canvas(100,100);

    for (uint32_t x = 0 ; x < WIDTH; ++x)
    {
        for (uint32_t y = 0; y < HEIGHT; ++y)
        {
            canvas_.DrawBlockLine(x * PIXEL_SIDE, y * PIXEL_SIDE, 
                            PIXEL_SIDE, PIXEL_SIDE, ftxui::Color::Red);
        }
    }
}

void GameDisplay::drawWindow() override
{
    drawPlayerBoard();
    auto document = ftxui::canvas(&canvas_) | ftxui::border;

    auto screen = Screen::create(ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    screen.Print();
}

