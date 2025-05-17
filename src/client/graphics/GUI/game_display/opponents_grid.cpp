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

#include "opponents_grid.hpp"

#include "opponent_widget.hpp"

#include <QChar>
#include <QFrame>
#include <QGridLayout>
#include <QPixmap>
#include <QWidget>
#include <QTimer>

namespace GUI {

    OpponentsGrid::OpponentsGrid(QWidget *parent) : QFrame(parent) {
        setLayout(&layout_);
    }

    void OpponentsGrid::setNthOpponent(size_t index, QPixmap *boardMap,
                                       const QString &name) {
        QString selectedStyleSheet{"background-color: blue;"};
        QString defaultStyleSheet{"background-color: none;"};

        if (QLayoutItem *pItem = layout_.itemAt(index)) {
            if (auto pWidget = pItem->widget()) {
                if (auto pOppWidget = qobject_cast<OpponentWidget *>(pWidget)) {
                    pOppWidget->setBoardMap(*boardMap);
                    pOppWidget->setName(name);

                    disconnect(pOppWidget, nullptr, nullptr, nullptr);
                    connect(pOppWidget, &OpponentWidget::clicked, this,
                            [index, this] { 
                                QTimer::singleShot(0, this, [this, index]() {
                                    emit selectTarget(index);
                                }); 
                            });
                }
            }
        } else { // not enough widgets in the layout yet.
            OpponentWidget *pOppWidget = new OpponentWidget{*boardMap, name};

            connect(pOppWidget, &OpponentWidget::clicked, this,
                    [index, this] { 
                        QTimer::singleShot(0, this, [this, index]() {
                            emit selectTarget(index);
                        });
                    });

            layout_.addWidget(pOppWidget);
        }
    }

    void OpponentsGrid::setSelectedTarget(int selectedOppIdx) {
        for (int i = 0; i < layout_.count(); i++) {
            if (QLayoutItem *pItem = layout_.itemAt(i)) {
                if (OpponentWidget *pOppWidget =
                        qobject_cast<OpponentWidget *>(pItem->widget())) {
                    bool isSelected = selectedOppIdx == i;

                    if (isSelected) {
                        pOppWidget->setFrameStyle(QFrame::Panel
                                                  | QFrame::Raised);
                        pOppWidget->setStyleSheet(
                            "QFrame { border: 3px solid yellow; }");
                    } else {
                        pOppWidget->setFrameStyle(QFrame::NoFrame);
                        pOppWidget->setStyleSheet("");
                    }
                }
            }
        }
    }

    void OpponentsGrid::setNumOpponents(size_t numOpponents) {
        while (layout_.count() > static_cast<int>(numOpponents)) {
            if (auto *pItem = layout_.takeAt(layout_.count() - 1)) {
                if (auto *pWidget = pItem->widget()) {
                    pWidget->deleteLater();
                }
                delete pItem;
            }
        }
    }

} // namespace GUI
