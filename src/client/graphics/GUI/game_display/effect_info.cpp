#include "effect_info.hpp"
#include <qwidget.h>

namespace GUI {

    EffectInfo::EffectInfo(QWidget *parent) : QFrame(parent) {
        progressBar_.setRange(MIN_PROGRESS, MAX_PROGRESS);

        layout_.addWidget(&effectName_);
        layout_.addWidget(&progressBar_);

        setLayout(&layout_);
    }

    void EffectInfo::setName(const QString &effectName) {
        effectName_.setText(effectName);
    }

    void EffectInfo::setProgress(double progress) {
        constexpr double percentageMultiplicator = 100;

        progressBar_.setValue(percentageMultiplicator * progress);
    }

} // namespace GUI
