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

#include "../game_display/game_display.hpp"

#include "../../../../common/types/types.hpp"

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

enum class GameMode; // Forward declaration

enum class JoinType {
    FRIEND,
    RANDOM,
    BACK,
    NONE,
};

enum class TypeGame {
    CREATE_GAME,
    JOIN_GAME,
    NONE,
};

/**
 * @brief Game menu class to show and select the game party
 *
 */
class GameMenu {
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
    void renderAllGames();

    /*
     * @brief Rend the game menu with just the online games mods
     */
    void renderOnlineGames();

    /*
     * @brief Screen to choose between joining a friend or a random game
     */
    void joinFriendOrRandomScreen();

    /*
     * @brief Handle the choice of the user in the game menu
     */
    void handleChoice();

    /*
     * @brief Screen when the user is joining a friend, a list of the online
     * friends is displayed and the user can select one
     */
    void joinFriendScreen();

    /*
     * @brief Screen when the is waiting for a random game
     */
    void joinRandomScreen();

    /*
     * @brief Screen when the user is waiting for the matchmaking
     */
    void createGameScreen();

    /*
     * @brief Make a button to add a friend
     */
    ftxui::Component makeFriendButton(UserID userID,
                                      const std::string &friendName);

    /*
     * @brief Screen when the user has choosen the friend and now waiting for
     * the start of the game
     */
    void waitingFriendScreen();

    /*
     * @brief The screen to select the number of player for the game
     */
    void selectPlayerCountScreen();

  public:
    /*
     * @brief Construct a new Game Menu object
     *
     * @param screen
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
    void render(const TypeGame &typeGame);
};

#endif // GAME_MENU_HPP
