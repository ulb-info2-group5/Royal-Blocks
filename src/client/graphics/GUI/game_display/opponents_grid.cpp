#include "opponents_grid.hpp"
#include "opponent_widget.hpp"

#include <QChar>
#include <QFrame>
#include <QGridLayout>
#include <QPixmap>
#include <QWidget>

#include <iostream>
#include <print>
#include <qframe.h>

namespace GUI {

    OpponentsGrid::OpponentsGrid(QWidget *parent) : QFrame(parent) {
        setLayout(&layout_);
    }

    void OpponentsGrid::setNthOpponent(size_t index, QPixmap *boardMap,
                                       const QString &name, bool isSelected) {
        QString selectedStyleSheet{"background-color: blue;"};
        QString defaultStyleSheet{"background-color: none;"};

        if (QLayoutItem *pItem = layout_.itemAt(index)) {
            if (auto pWidget = pItem->widget()) {
                if (auto pOppWidget = qobject_cast<OpponentWidget *>(pWidget)) {
                    pOppWidget->setBoardMap(*boardMap);
                    pOppWidget->setName(name);

                    if (isSelected) {
                        pOppWidget->setFrameStyle(QFrame::Panel
                                                  | QFrame::Raised);
                        pOppWidget->setStyleSheet(
                            "QFrame { border: 3px solid yellow; }");
                    } else {
                        pOppWidget->setFrameStyle(QFrame::NoFrame);
                    }

                    disconnect(pOppWidget, nullptr, nullptr, nullptr);
                    connect(pOppWidget, &OpponentWidget::clicked, this,
                            [index, this] {
                                std::println(std::cerr,
                                             "sending signal: selected {}",
                                             index);
                                emit selectTarget(index);
                            });
                }
            }
        } else { // not enough widgets in the layout yet.
            std::println(std::cerr, "new OpponentWidget");
            OpponentWidget *pOppWidget = new OpponentWidget{*boardMap, name};

            connect(pOppWidget, &OpponentWidget::clicked, this, [index, this] {
                std::println(std::cerr, "sending signal: selected {}", index);
                emit selectTarget(index);
            });

            layout_.addWidget(pOppWidget);
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
