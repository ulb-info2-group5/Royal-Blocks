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

#include "opponent_widget.hpp"

#include <QTimer>

namespace GUI {

    OpponentWidget::OpponentWidget(const QPixmap &pixmap,
                                   const QString &nickname, QWidget *parent)
        : QFrame(parent) {

        boardLabel_.setPixmap(pixmap);
        boardLabel_.setAlignment(Qt::AlignCenter);

        nameLabel_.setAlignment(Qt::AlignCenter);
        nameLabel_.setText(nickname);

        layout_.addWidget(&boardLabel_);
        layout_.addWidget(&nameLabel_);
        setLayout(&layout_);
    }

    void OpponentWidget::mousePressEvent(QMouseEvent *event) {
        QTimer::singleShot(0, this, [this]() {
            emit clicked();
        });
        QWidget::mousePressEvent(event);
    }

    void OpponentWidget::setBoardMap(const QPixmap &pixmap) {
        boardLabel_.setPixmap(pixmap);
    }

    void OpponentWidget::setName(const QString &name) {
        nameLabel_.setText(name);
    }

} // namespace GUI
