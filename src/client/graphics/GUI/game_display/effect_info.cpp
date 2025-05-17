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

#include "effect_info.hpp"

#include <QWidget>

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
