/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GUI_GAME_DISPLAY_HPP
#define GUI_GAME_DISPLAY_HPP

#include "../../common/abstract_game_display.hpp"
#include "effect_info.hpp"
#include "effects_selector.hpp"
#include "opponents_grid.hpp"

#include <QLCDNumber>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>


class Controller;

namespace GUI {

    class TetrisWindow;

    enum class CellSize : size_t {
        Small = 10,
        Big = 40,
    };

    /**
     * @brief Widget that displays the "in game" window.
     * Contains multiple subwidgets such as:
     * - Player's board
     * - LCD with the score
     * - LCD with the energy
     * - The tetraminoes queue
     * - Info about penalty and effects
     * - available-effects
     * - Quit bouton.
     */
    class GameDisplay final : public QWidget, public AbstractGameDisplay {

        Q_OBJECT

      private:
        TetrisWindow &tetrisWindow_;
        QStackedWidget stackedWidget_;
        QLCDNumber scoreLCD_;
        QLCDNumber energyLCD_;
        QLabel holdTetromino_;
        EffectInfo bonusInfo_;
        EffectInfo penaltyInfo_;
        EffectSelector effectSelector_;
        QLabel selfBoard_;
        QLabel tetrominoQueue_;
        QHBoxLayout middlePaneHBox_;
        QVBoxLayout middlePaneLeftVBox_;
        OpponentsGrid opponentsGrid_;
        int dynamicCellSize_ = 40;

        /**
         * @brief Redraws the board pixmap and returns a pointer to the QLable
         * containing the board pixmap.
         */
        void selfBoard(int cellSize = -1);

        void scoreLCD();
        void holdTetromino();
        void energyLCD();
        void tetrominoQueue();
        QPixmap createOppBoardMap(size_t index, CellSize size);
        void oppBoards();
        void bonusInfo();
        void penaltyInfo();
        void effectsInfo();
        void effectSelector();
        void setup();

        void updateDynamicCellSize();

      private slots:
        void on_QuitButtonClicked();
        void on_EffectBought(EffectType effect);
        void on_TargetSelected(size_t targetIdx);
        void on_ReturnToMainMenuButtonClicked();
        void updateGameState();

      protected:
        void keyPressEvent(QKeyEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;

      public:
        GameDisplay(Controller &controller, TetrisWindow &tetrisWindow,
                    QWidget *parent = nullptr);

        ~GameDisplay() = default;

      signals:
        void backToMainMenu();
    };

} // namespace GUI

#endif
