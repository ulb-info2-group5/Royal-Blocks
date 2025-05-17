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

#ifndef GUI_EFFECT_INFO_HPP
#define GUI_EFFECT_INFO_HPP

#include <QChar>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace GUI {

    /**
     * @brief A widget that displays information about an effect applied to
     * the player.
     *
     * This widget shows the effect's name and a progress bar indicating how
     * much time has elapsed relative to the effect's total duration.
     */
    class EffectInfo : public QFrame {

        Q_OBJECT

      private:
        QHBoxLayout layout_;
        QLabel effectName_;
        QProgressBar progressBar_;
        static constexpr int MIN_PROGRESS = 0;
        static constexpr int MAX_PROGRESS = 100;

      public:
        EffectInfo(QWidget *parent = nullptr);

        void setName(const QString &effectName);

        void setProgress(double progress);
    };

} // namespace GUI

#endif // GUI_EFFECT_INFO_HPP
