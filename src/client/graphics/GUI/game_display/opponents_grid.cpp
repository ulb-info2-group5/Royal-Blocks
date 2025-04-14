#include "opponents_grid.hpp"

#include "opponent_widget.hpp"

#include <QChar>
#include <QFrame>
#include <QGridLayout>
#include <QPixmap>
#include <QWidget>

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
                            [index, this] { emit selectTarget(index); });
                }
            }
        } else { // not enough widgets in the layout yet.
            OpponentWidget *pOppWidget = new OpponentWidget{*boardMap, name};

            connect(pOppWidget, &OpponentWidget::clicked, this,
                    [index, this] { emit selectTarget(index); });

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
