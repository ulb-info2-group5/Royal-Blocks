#ifndef TUI_GAME_DISPLAY_HPP
#define TUI_GAME_DISPLAY_HPP

#include "../../../../common/types/types.hpp"

#include "../../common/abstract_game_display.hpp"

#include <ftxui/component/component.hpp>

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

class Controller;

namespace TUI {

    class MainTui;

    enum class CellSize : size_t {
        Small = 4,
        Big = 8,
    };

    constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 10,
                     HEIGHT_CANVAS_BIG =
                         static_cast<size_t>(CellSize::Big) * 20,
                     WIDTH_CANVAS_SMALL =
                         static_cast<size_t>(CellSize::Small) * 10,
                     HEIGHT_CANVAS_SMALL =
                         static_cast<size_t>(CellSize::Small) * 20;

    class GameDisplay final : public AbstractGameDisplay {
      private:
        MainTui &mainTui_;

        ftxui::Component displayWindow_;

        /**
         * @brief Returns a new component containing the board of the index-th
         * opponent.
         */
        ftxui::Component createOpBoardDisplay(size_t index, CellSize cellSize);

        ftxui::Component quitButton();
        ftxui::Component playerInfo();
        ftxui::Component energy();
        ftxui::Component availableEffects();
        ftxui::Component penaltyInfo();
        ftxui::Component bonusInfo();
        ftxui::Component holdTetromino();
        ftxui::Component leftPane();

        ftxui::Component gameMode();
        ftxui::Component selfBoard(CellSize size = CellSize::Big);
        ftxui::Component tetrominoQueue();
        ftxui::Component middlePane();

        ftxui::Component opponentsBoards();

        ftxui::Component rightPane();

        ftxui::Component &drawEndlessMode();

        ftxui::Component &drawMultiMode();

        ftxui::Component &drawGameOver();

        ftxui::Component &drawWin();

        ftxui::Component &drawSpectate();

        void handleKeys();

      public:
        /*
         * @brief Constructor for the GameDisplay class
         *
         * @param screenManager The screen manager to use
         * @param controller The controller to use
         */
        GameDisplay(MainTui &screenManager, Controller &controller);

        ~GameDisplay() = default;

        /*
         * @brief Render the game display
         */
        void render();
    };

} // namespace TUI

#endif // TUI_GAME_DISPLAY_HPP
