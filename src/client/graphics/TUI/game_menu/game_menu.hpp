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
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

#include "../../IGame_Menu.hpp"
#include "../game_display/game_display.hpp" 
#include "game_mode/game_mode.hpp"

using PlayerID = size_t;

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

/**
 * @brief Game menu class to show and select the game party
 *
 */
class GameMenu final : public IGame_Menu {
  private:
    ScreenManager &screenManager_;
    Controller &controller_;

    std::unique_ptr<GameDisplay> gameDisplay_;

    JoinType joinType_;

    GameMode gameMode_;

    TypeGame typeGame_;

    bool quitMenu_;

    /**
     * @brief The button components that can be in the game menu
     *
     */
    ftxui::Component endlessButon_;
    ftxui::Component duelButon_;
    ftxui::Component classicButon_;
    ftxui::Component royalButon_;
    ftxui::Component backButton_;
    ftxui::Component quitMenuButton_;

    /*
     * @brief Rend the all the game present in the game menu
     */
    void renderAllGames() override;

    /*
     * @brief Rend the game menu with just the online games mods
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
     * @brief Screen when the user is waiting for the matchmaking
     */
    void matchmakingScreen() override;

    /*
     * @brief Make a button to add a friend
     *
     * @param playerId The id of the player to add as a friend
     * @param friendName The name of the friend to add
     * @return ftxui::Component The button to add a friend
     */
    ftxui::Component makeFriendButton(PlayerID playerId,
                                      const std::string &friendName);

    /*
     * @brief Screen when the user has choosen the friend and now waiting for
     * the start of the game
     */
    void waitingFriendScreen() override;

    /*
     * @brief The screen to select the number of player for the game
     */
    void selectPlayerCountScreen() override;

  public:
    /*
     * @brief Construct a new Game Menu object
     *
     * @param screenManager The screen manager for asking to render the components
     * @param controller The controller to interact with the server
     */
    GameMenu(ScreenManager &screenManager, Controller &controller);

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
