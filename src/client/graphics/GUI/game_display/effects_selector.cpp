#include "effects_selector.hpp"

#include <QPushButton>

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
    const std::vector<std::pair<EffectType, Energy>> &effectPrices) {

    clear();

    for (auto [effectType, effectPrice] : effectPrices) {
        auto *button = new QPushButton(QString::fromStdString(
            std::format("{} {}", toString(effectType), effectPrice)));

        layout_.addWidget(button);

        connect(button, &QPushButton::clicked, this,
                [this, effectType]() { emit buyEffect(effectType); });
    }
}
