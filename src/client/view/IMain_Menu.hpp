#ifndef IMAIN_MENU_HPP
#define IMAIN_MENU_HPP

class IMain_Menu {
  protected:
    virtual void displayMainMenuButtons() = 0;

    virtual void displayMainWindow() = 0;

    virtual void displayRankingList() = 0;

    virtual void displayRankingWindow() = 0;

    virtual void displayProfileManagerButton() = 0;

    virtual void displayProfileManagerWindow() = 0;

  public:
    virtual ~IMain_Menu() = default;

    virtual void renderRanking() = 0;

    virtual void renderProfileManager() = 0;
};

#endif