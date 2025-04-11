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
        layout_.addWidget(new QPushButton(QString::fromStdString(
            std::format("{} {}", toString(effectType), effectPrice))));
    }
}
