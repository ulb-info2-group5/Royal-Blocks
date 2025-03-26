#include "rankinggui.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollArea>

#include "../../../core/controller/controller.hpp"

RankingGui::RankingGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {

    backButton.setText("Back");
    backButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    backButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    setupRankingGuiTable();

    connect(&backButton, &QPushButton::clicked, this, &RankingGui::on_BackButtonClicked);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->addWidget(&RankingGuiTable);
    scrollLayout->addWidget(&backButton);
    scrollWidget->setLayout(scrollLayout);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scrollArea, 1);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

}

void RankingGui::on_BackButtonClicked() {
    emit backToMainMenu();
}

/*--------------------------------------------------------
                    Private Methods
---------------------------------------------------------*/


void RankingGui::setupRankingGuiTable() {
    std::vector<std::pair<std::string, Score>> RankingGuiData = controller_->getRanking();

    RankingGuiTable.setRowCount(RankingGuiData.size());
    RankingGuiTable.setColumnCount(2);
    RankingGuiTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    RankingGuiTable.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    RankingGuiTable.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QStringList headers;
    headers << "Player" << "Score";
    RankingGuiTable.setHorizontalHeaderLabels(headers);

    for (size_t i = 0; i < RankingGuiData.size(); ++i) {
        QTableWidgetItem *playerItem = new QTableWidgetItem(QString::fromStdString(RankingGuiData[i].first));
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(RankingGuiData[i].second));

        RankingGuiTable.setItem(i, 0, playerItem);
        RankingGuiTable.setItem(i, 1, scoreItem);
    }

    RankingGuiTable.horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    RankingGuiTable.horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}
