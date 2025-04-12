#include "opponent_widget.hpp"

#include <print>

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
        emit clicked();
        QWidget::mousePressEvent(event);
    }

} // namespace GUI
