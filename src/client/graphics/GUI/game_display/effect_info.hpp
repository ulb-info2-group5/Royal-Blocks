#ifndef GUI_EFFECT_INFO_HPP
#define GUI_EFFECT_INFO_HPP

#include <QChar>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace GUI {

    class EffectInfo : public QFrame {
      /**
      * @brief It show widget progress bar for "energy" to use to do effect; malus and bonus.
      * It show to the name of current effect.
      */
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
