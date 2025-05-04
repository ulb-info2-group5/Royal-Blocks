#ifndef GUI_OPPONENT_WIDGET_HPP
#define GUI_OPPONENT_WIDGET_HPP

#include <QChar>
#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace GUI {

    /**
     * @brief Displays the opponent's board and username. Allows the
     * widget to be selected (signal will be sent in such case).
     */
    class OpponentWidget : public QFrame {
        Q_OBJECT

      public:
        OpponentWidget(const QPixmap &pixmap, const QString &nickname,
                       QWidget *parent = nullptr);

        void setBoardMap(const QPixmap &pixmap);

        void setName(const QString &name);

      signals:
        void clicked();

      protected:
        void mousePressEvent(QMouseEvent *event) override;

      private:
        QGridLayout layout_;
        QLabel boardLabel_;
        QLabel nameLabel_;
    };

} // namespace GUI

#endif // GUI_OPPONENT_WIDGET_HPP
