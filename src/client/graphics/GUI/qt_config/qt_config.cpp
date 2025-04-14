#include "qt_config.hpp"

#include <QFont>

namespace GUI {

    QLabel *createCenterBoldTitle(const std::string_view &title) {
        QLabel *titleLabel = new QLabel(title.data());
        QFont boldFont = titleLabel->font();
        boldFont.setBold(true);
        boldFont.setPointSize(20);
        titleLabel->setFont(boldFont);
        titleLabel->setAlignment(Qt::AlignCenter);
        return titleLabel;
    }

} // namespace GUI
