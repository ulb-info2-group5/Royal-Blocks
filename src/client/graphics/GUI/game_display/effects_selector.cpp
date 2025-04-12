#include "effects_selector.hpp"

#include <QLayout>
#include <QLayoutItem>
#include <QObject>
#include <QPushButton>
#include <QStyle>

namespace GUI {

    EffectSelector::EffectSelector(QWidget *parent) : QFrame(parent) {
        setLayout(&layout_);
    }

    void EffectSelector::clear() {
        for (int i = 0; i < layout_.count(); ++i) {
            auto tmp = layout_.takeAt(i);
            if (tmp != nullptr) {
                tmp->widget()->deleteLater();
            }
        }
    }

    void EffectSelector::setEffectPrices(
        const std::vector<std::pair<EffectType, Energy>> &effectPrices,
        EffectType selectedEffectType) {

        for (size_t i = 0; i < effectPrices.size(); i++) {
            auto [effectType, effectPrice] = effectPrices.at(i);

            QString buttonText = QString::fromStdString(
                std::format("{} {}", toString(effectType), effectPrice));

            bool isSelected = effectType == selectedEffectType;

            if (QLayoutItem *pItem = layout_.itemAt(i)) {
                if (auto pWidget = pItem->widget()) {
                    if (auto pButton = qobject_cast<QPushButton *>(pWidget)) {
                        pButton->setText(buttonText);

                        if (isSelected) {
                            pButton->setStyleSheet(selectedStyleSheet_);
                        } else {
                            pButton->setStyleSheet(defaultStyleSheet_);
                        }

                        disconnect(pButton, nullptr, nullptr, nullptr);
                        connect(pButton, &QPushButton::clicked, this,
                                [this, effectType]() {
                                    emit buyEffect(effectType);
                                });
                    }
                }
            } else { // not enough buttons in the layout yet.
                QPushButton *pButton = new QPushButton(buttonText);

                connect(pButton, &QPushButton::clicked, this,
                        [this, effectType]() { emit buyEffect(effectType); });

                layout_.addWidget(pButton);
            }
        }

        while (layout_.count() > static_cast<int>(effectPrices.size())) {
            if (auto *pItem = layout_.takeAt(layout_.count() - 1)) {
                if (auto *pWidget = pItem->widget()) {
                    pWidget->deleteLater();
                }
                delete pItem;
            }
        }
    }

} // namespace GUI
