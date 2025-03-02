#ifndef IMAIN_MENU_HPP
#define IMAIN_MENU_HPP

enum class MainMenuState {
    CREATE_GAME,
    JOIN_GAME,
    SEND_MESSAGES_TO_FRIENDS,
    LOOK_RANKING,
    MANAGE_PROFILE,
    MANAGE_FRIENDS_LIST,
    EXIT,
    BACK,
    NONE,
};

class IMain_Menu {

  private : 
    virtual void handleChoice() = 0;

    virtual void confirmUpdateProfileScreen() const = 0;
    
  protected:
    virtual void displayMainMenuButtons() = 0;

    virtual void displayMainWindow() = 0;

    virtual void displayRankingList() = 0;

    virtual void displayRankingWindow() = 0;

    virtual void displayProfileManagerButton() = 0;

    virtual void displayProfileManagerWindow() = 0;

    virtual void renderRanking() = 0;

    virtual void renderProfileManager() = 0;

  public:
    virtual ~IMain_Menu() = default;

    virtual void render() = 0;
};

#endif