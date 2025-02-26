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
#include <ftxui/component/component.hpp>
#include <memory>
#include <cstdint>

class Controller; // Forward declaration

/**
 * @brief Game menu class to show and selct the game party
 * 
 */
class GameMenu {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;
        Controller *controller_;


        /**
         * @brief The button components that can be in the game menu    
         * 
         */
        ftxui::Component endlessButon_;
        ftxui::Component duelButon_;
        ftxui::Component classicButon_;
        ftxui::Component royalButon_;
        ftxui::Component backButton_;

    public:
        /*
         * @brief Construct a new Game Menu object
         * 
         * @param screen 
         */
        GameMenu(std::shared_ptr<ftxui::ScreenInteractive> screen, Controller *controller);

        /*
         * @brief Destroy the Game Menu object
         */
        ~GameMenu() = default;

        /*
         * @brief Rend the all the game present in the game menu
         *
         * @return PlayMode the game mode selected
         */
         void renderAllGames();

         /*
         * @brief Rend the game menu with just the online games mods
         * @return PlayMode the game mode selected
         */
         void renderOnlineGames();
};

#endif // GAME_MENU_HPP