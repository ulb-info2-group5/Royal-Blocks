#ifndef IGAME_MENU_HPP
#define IGAME_MENU_HPP

enum class JoinType {
    FRIEND,
    RANDOM,
    BACK,
    GAME_FINISHED,
    NONE,
};

enum class TypeGame {
    CREATE_GAME,
    JOIN_GAME,
    NONE,
};

class IGame_Menu {
  private:
    virtual void renderAllGames() = 0;

    /*
     * @brief Rend the game menu with just the online games mods
     * @return PlayMode the game mode selected
     */
    virtual void renderOnlineGames() = 0;

    /*
     * @brief Screen to choose between joining a friend or a random game
     */
    virtual void joinFriendOrRandomScreen() = 0;

    /*
     * @brief Handle the choice of the user in the game menu
     */
    virtual void handleChoice() = 0;

    /*
     * @brief Screen when the user is joining a friend, a list of the online
     * friends is displayed and the user can select one
     */
    virtual void joinFriendScreen() = 0;

    /*
     * @brief Screen when the is waiting for a random game
     */
    virtual void joinRandomScreen() = 0;

    virtual void waitingFriendScreen() = 0;

    virtual void matchmakingScreen() = 0;

    virtual void selectPlayerCountScreen() = 0;

  public:
    virtual ~IGame_Menu() = default;

    virtual void render(const TypeGame &typeGame) = 0;
};

#endif