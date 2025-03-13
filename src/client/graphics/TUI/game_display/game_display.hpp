#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../IGame.hpp"
#include "../../interfaceConstants.hpp"

#include <ftxui/component/component.hpp>

#include <string>
#include <vector>

constexpr uint32_t LENGTH_PLAYER = 8, LENGTH_OPPONENT = 2, PADDING = 10;

constexpr uint32_t WIDTH_PLAYER_CANVAS = 80, HEIGHT_PLAYER_CANVAS = 160,
                   WIDTH_OP_CANVAS = 20, HEIGHT_OP_CANVAS = 40;

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

ftxui::Color getFTXUIColor(Color color);

class GameDisplay final : public IGame {
  private:
    ScreenManager &screenManager_;

    Controller &controller_;

    // TODO: remove this
    std::vector<std::string> pseudos_;
    // float penaltyGauge_;
    std::vector<std::string> effects_ = {};

    ftxui::Component playerInfo_;
    ftxui::Component effectsDisplay_;
    ftxui::Component playerBoard_;
    ftxui::Components opBoards_;
    ftxui::Component opBoardDisplay_;

    ftxui::Component displayRight_;
    ftxui::Component displayMiddle_;
    ftxui::Component displayLeft_;
    ftxui::Component displayWindow_;

    void drawPlayerInfo() override;

    void drawRoyalEffectsEnergy() override;

    void displayLeftWindow() override;

    void drawPlayerBoard() override;

    void displayMiddleWindow() override;

    void drawOpponentsBoard() override;

    void displayOpponentBoardDuel() override;

    void displayOppponentsBoard() override;

    void displayMultiRightWindow() override;

    void drawEndlessMode() override;

    void drawMultiMode() override;

    void handleKeys() override;

    void updateDisplay() override;

  public:
    GameDisplay(ScreenManager &screenManager, Controller &controller);

    ~GameDisplay() = default;

    void render() override;
};

#endif
