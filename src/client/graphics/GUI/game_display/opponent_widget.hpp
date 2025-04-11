#ifndef GUI_OPPONENT_WIDGET_HPP
#define GUI_OPPONENT_WIDGET_HPP

#include <QColor>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <qchar.h>
#include <qcolor.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpushbutton.h>

class OpponentWidget : public QFrame {
    Q_OBJECT

  public:
    OpponentWidget(const QPixmap &pixmap, const QString &nickname,
                   bool isSelected, QWidget *parent = nullptr);

  signals:
    void clicked();

  protected:
    void mousePressEvent(QMouseEvent *event) override;

  private:
    QVBoxLayout layout_;
    QLabel boardLabel_;
    QLabel nameLabel_;
};

#endif // GUI_OPPONENT_WIDGET_HPP
