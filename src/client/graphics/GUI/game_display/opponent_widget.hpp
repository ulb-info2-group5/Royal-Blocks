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

#ifndef GUI_OPPONENT_WIDGET_HPP
#define GUI_OPPONENT_WIDGET_HPP

#include <QChar>
#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace GUI {

    /**
     * @brief Displays the opponent's board and username. Allows the
     * widget to be selected (signal will be sent in such case).
     */
    class OpponentWidget : public QFrame {
        Q_OBJECT

      public:
        OpponentWidget(const QPixmap &pixmap, const QString &nickname,
                       QWidget *parent = nullptr);

        void setBoardMap(const QPixmap &pixmap);

        void setName(const QString &name);

      signals:
        void clicked();

      protected:
        void mousePressEvent(QMouseEvent *event) override;

      private:
        QGridLayout layout_;
        QLabel boardLabel_;
        QLabel nameLabel_;
    };

} // namespace GUI

#endif // GUI_OPPONENT_WIDGET_HPP
