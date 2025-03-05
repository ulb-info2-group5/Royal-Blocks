/**
 * @file game_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class declaration file
 * @date 2025-02-24
 *
 */

#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

#include "../../IGame_Menu.hpp"
#include "../game_display/game_display.hpp"

class Controller; // Forward declaration

/**
 * @brief Game menu class to show and select the game party
 *
 */
class GameMenu : public IGame_Menu {
  private:
    ftxui::ScreenInteractive &screen_;
    Controller *controller_;

    std::unique_ptr<GameDisplay> gameDisplay_;

    JoinType joinType_;

    TypeGame typeGame_;

    /**
     * @brief The button components that can be in the game menu
     *
     */
    ftxui::Component endlessButon_;
    ftxui::Component duelButon_;
    ftxui::Component classicButon_;
    ftxui::Component royalButon_;
    ftxui::Component backButton_;

    /*
     * @brief Rend the all the game present in the game menu
     *
     * @return PlayMode the game mode selected
     */
    void renderAllGames() override;

    /*
     * @brief Rend the game menu with just the online games mods
     * @return PlayMode the game mode selected
     */
    void renderOnlineGames() override;

    /*
     * @brief Screen to choose between joining a friend or a random game
     */
    void joinFriendOrRandomScreen() override;

    /*
     * @brief Handle the choice of the user in the game menu
     */
    void handleChoice() override;

    /*
     * @brief Screen when the user is joining a friend, a list of the online
     * friends is displayed and the user can select one
     */
    void joinFriendScreen() override;

    /*
     * @brief Screen when the is waiting for a random game
     */
    void joinRandomScreen() override;

    /*
     * @brief Make a button to add a friend
     *
     * @param friendName The name of the friend to add
     */
    ftxui::Component makeFriendButton(const std::string &friendName);

    /*
     * @brief Screen when the user has choosen the friend and now waiting for
     * the start of the game
     */
    void waitingFriendScreen() override;

  public:
    /*
     * @brief Construct a new Game Menu object
     *
     * @param screen
     */
    GameMenu(ftxui::ScreenInteractive &screen,
             Controller *controller);

    /*
     * @brief Destroy the Game Menu object
     */
    ~GameMenu() = default;

    /*
     * @brief Render the game menu
     *
     * @param typeGame The type of the game to render
     */
    void render(const TypeGame &typeGame) override;
};

#endif // GAME_MENU_HPP
