#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../../core/in_game/game_state_wrapper.hpp"
#include "../../IGame.hpp"
#include "../../interfaceConstants.hpp"

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/color.hpp" // for Color

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <memory>
#include <string>
#include <vector>

constexpr uint32_t LENGTH_PLAYER = 7, LENGTH_OPPONENT = 3, PADDING = 10;

constexpr uint32_t WIDTH_PLAYER_CANVAS = 70, HEIGHT_PLAYER_CANVAS = 140,
               WIDTH_OP_CANVAS = 30, HEIGHT_OP_CANVAS = 60;

class Controller; // Forward declaration

ftxui::Color getFTXUIColor(Color color);

class GameDisplay : public IGame {
  private:
    ftxui::ScreenInteractive &screen_;

    Controller &controller_;

    std::shared_ptr<client::GameStateWrapper> pGameState_;

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

  protected:
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

  public:
    GameDisplay(ftxui::ScreenInteractive &screen, Controller &controller,
                std::shared_ptr<client::GameStateWrapper> &pGameState);

    ~GameDisplay() = default;

    void render() override;
};

#endif
