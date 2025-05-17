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

#ifndef GUI_RANKING_HPP
#define GUI_RANKING_HPP

#include <QTableWidget>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    /**
     * @brief Displays the ranking of all players.
     */
    class Ranking : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;

        TetrisWindow &tetrisWindow_;

        QTableWidget rankingTable_;

        /*
         * @brief Setup the UI
         */
        void setupUI();

        /*
         * @brief Setup the ranking Table
         */
        void setupRankingTable();

        /*
         * @brief Update the ranking Table
         */
        void updateRankingTable();

      public:
        Ranking(Controller &controller, TetrisWindow &tetrisWindow,
                QWidget *parent = nullptr);

        ~Ranking() = default;

      signals:
        /*
         * @brief Signal emitted when the user click on the back button
         */
        void backToMainMenu();

      public slots:
        /*
         * @brief Action to perform when the user click on the back button
         */
        void on_BackButtonClicked();
    };

} // namespace GUI

#endif // GUI_RANKING_HPP
