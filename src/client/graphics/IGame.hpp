#ifndef IGAME_HPP
#define IGAME_HPP

enum class PlayMode { CLASSIC, ROYAL, DUEL, ENDLESS, NONE };

class IGame {
  protected:
    virtual void drawPlayerInfo() = 0;

    virtual void drawRoyalEffectsEnergy() = 0;

    virtual void displayLeftWindow() = 0;

    virtual void drawPlayerBoard() = 0;

    virtual void displayMiddleWindow() = 0;

    virtual void drawOpponentsBoard() = 0;

    virtual void displayOppponentsBoard() = 0;

    virtual void displayOpponentBoardDuel() = 0;

    virtual void displayMultiRightWindow() = 0;

    virtual void drawEndlessMode() = 0;

    virtual void drawMultiMode() = 0;

    virtual void handleKeys() = 0;

    virtual void updateDisplay() = 0;

  public:
    virtual ~IGame() = default;

    virtual void render() = 0;
};

#endif