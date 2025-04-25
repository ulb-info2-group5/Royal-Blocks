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
