#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"
#include "../../../core/in_game/game_state/game_state.hpp"
#include <ftxui/component/component.hpp>

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

enum class CellSize : size_t {
    Small = 4,
    Big = 8,
};

constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 10,
                 HEIGHT_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 20,
                 WIDTH_CANVAS_SMALL = static_cast<size_t>(CellSize::Small) * 10,
                 HEIGHT_CANVAS_SMALL =
                     static_cast<size_t>(CellSize::Small) * 20;

class MainTui; // Forward declaration

class Controller; // Forward declaration

enum class Color {
    Black,
    White,
    Grey,
    DarkBlue,
    LightBlue,
    Purple,
    Red,
    Orange,
    Pink,
    Green,
    Yellow
};

class GameDisplay final {
  public:
    // Returned by selfCellInfoAt.
    // Tells us whether the cell at (x,y) is the part of the active or preview
    // or a placed Tetromino.
    enum class SelfCellType {
        Active,
        Preview,
        Placed,
    };

  private:
    MainTui &mainTui_;

    Controller &controller_;

    client::GameState gameState_;

    ftxui::Component quitButton_;
    ftxui::Component playerInfo_;
    ftxui::Component energy_;
    ftxui::Component availableEffects_;
    ftxui::Component penaltyInfo_;
    ftxui::Component bonusInfo_;
    ftxui::Component leftPane_;

    ftxui::Component gameMode_;
    ftxui::Component selfBoard_;
    ftxui::Component middlePane_;

    ftxui::Component opponentsBoards_;
    ftxui::Component rightPane_;

    ftxui::Component displayWindow_;

    /**
     * @brief Returns a new component containing the board of the index-th
     * opponent.
     */
    ftxui::Component createOpBoardDisplay(size_t index, CellSize cellSize);

    ftxui::Component &quitButton();
    ftxui::Component &playerInfo();
    ftxui::Component &energy();
    ftxui::Component &availableEffects();
    ftxui::Component &penaltyInfo();
    ftxui::Component &bonusInfo();
    ftxui::Component &leftPane();

    ftxui::Component &gameMode();
    ftxui::Component &selfBoard(CellSize size = CellSize::Big);
    ftxui::Component &middlePane();

    ftxui::Component &opponentsBoards();

    ftxui::Component &rightPane();

    ftxui::Component &drawEndlessMode();

    ftxui::Component &drawMultiMode();

    ftxui::Component &drawGameOver();

    ftxui::Component &drawWin();

    UserID getNthOpponentUserID(size_t n) const;

    void handleKeys();

    size_t getBoardHeight() const;

    size_t getBoardWidth() const;

    Score getSelfScore() const;

    Score getSelfEnergy() const;

    GameMode getGameMode() const;

    std::optional<std::pair<unsigned, SelfCellType>>
    selfCellInfoAt(int x, int y) const;

    std::string getSelfUsername() const;

    std::optional<unsigned> opponentsBoardGetColorIdAt(size_t opponentIdx,
                                                       int x, int y) const;

    std::string getOpponentUsername(size_t opponentIdx) const;

    size_t getNumOpponents() const;

    const std::vector<std::pair<EffectType, Energy>> &getEffectPrices() const;

    bool inGame() const;

  public:
    GameDisplay(MainTui &screenManager, Controller &controller);

    ~GameDisplay() = default;

    void render();
};

#endif
