#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../IGame.hpp"
#include "../../interfaceConstants.hpp"

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/color.hpp" // for Color

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <array>
#include <memory>
#include <string>
#include <vector>

const uint32_t LENGTH_PLAYER = 4, LENGTH_OPPONENT = 2, PADDING = 10;

const uint32_t WIDTH_PLAYER_CANVAS = 40, HEIGHT_PLAYER_CANVAS = 80,
               WIDTH_OP_CANVAS = 20, HEIGHT_OP_CANVAS = 40;

class Controller; // Forward declaration

ftxui::Color getFTXUIColor(colors color);

class GameDisplay : public IGame {
  private:
    std::shared_ptr<ftxui::ScreenInteractive> screen_;
    Controller *controller_;

    std::vector<std::string> pseudos_;
    std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>
        playersBoards_;
    uint32_t score_;
    float malusGauge_;
    PlayMode play_;

    float energyGauge_;
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

  public:
    GameDisplay(std::shared_ptr<ftxui::ScreenInteractive> screen,
                Controller *controller,
                std::shared_ptr<
                    std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>
                    boards,
                PlayMode play);

    ~GameDisplay() = default;

    void render() override;
};

#endif