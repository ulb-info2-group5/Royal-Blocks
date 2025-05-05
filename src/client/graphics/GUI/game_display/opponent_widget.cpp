#include "opponent_widget.hpp"

#include <QTimer>

namespace GUI {

    OpponentWidget::OpponentWidget(const QPixmap &pixmap,
                                   const QString &nickname, QWidget *parent)
        : QFrame(parent) {

        boardLabel_.setPixmap(pixmap);
        boardLabel_.setAlignment(Qt::AlignCenter);

        nameLabel_.setAlignment(Qt::AlignCenter);
        nameLabel_.setText(nickname);

        layout_.addWidget(&boardLabel_);
        layout_.addWidget(&nameLabel_);
        setLayout(&layout_);
    }

    void OpponentWidget::mousePressEvent(QMouseEvent *event) {
        QTimer::singleShot(0, this, [this]() {
            emit clicked();
        });
        QWidget::mousePressEvent(event);
    }

    void OpponentWidget::setBoardMap(const QPixmap &pixmap) {
        boardLabel_.setPixmap(pixmap);
    }

    void OpponentWidget::setName(const QString &name) {
        nameLabel_.setText(name);
    }

} // namespace GUI
