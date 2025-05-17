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

#ifndef GUI_OPPONENTS_GRID
#define GUI_OPPONENTS_GRID

#include <QFrame>
#include <QGridLayout>
#include <QWidget>

namespace GUI {

    /**
    * @brief 
    * Display during the game the opponents grids.
    * Allows to select an opponent like target.
    */

    class OpponentsGrid : public QFrame {
        Q_OBJECT

      private:
        QHBoxLayout layout_;

      public:
        OpponentsGrid(QWidget *parent = nullptr);

        void setNthOpponent(size_t index, QPixmap *boardMap,
                            const QString &name);

        void setSelectedTarget(int selectedOppIdx);

        void setNumOpponents(size_t numOpponents);

      signals:
        void selectTarget(size_t targetNum);
    };

}; // namespace GUI

#endif // GUI_OPPONENTS_GRID
