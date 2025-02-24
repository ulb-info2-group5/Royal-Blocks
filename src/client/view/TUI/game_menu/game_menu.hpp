/**
 * @file game_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class declaration file
 * @date 2025-02-24
 * 
 */

#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <cstdint>

enum class PlayMode : uint8_t 
{
    ENDLESS,
    DUEL   ,
    CLASSIC,
    ROYAL,
    NONE,
};

/**
 * @brief Game menu class to show and selct the game party
 * 
 */
class GameMenu {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

    public:
        /*
         * @brief Construct a new Game Menu object
         * 
         * @param screen 
         */
        GameMenu(std::shared_ptr<ftxui::ScreenInteractive> screen);

        /*
         * @brief Destroy the Game Menu object
         */
        ~GameMenu() = default;

        /*
         * @brief Rend the game menu
         */
         PlayMode render();
};

#endif // GAME_MENU_HPP