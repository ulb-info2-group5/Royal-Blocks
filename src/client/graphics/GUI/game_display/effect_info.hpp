#ifndef GUI_EFFECT_INFO_HPP
#define GUI_EFFECT_INFO_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <qchar.h>
#include <qprogressbar.h>

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

#endif // GUI_EFFECT_INFO_HPP
