#include "rankinggui.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

#include "../../../core/controller/controller.hpp"

RankingGui::RankingGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {

    RankingGuiTable = new QTableWidget();
    backButton = new QPushButton("Back");

    setupRankingGuiTable();

    connect(backButton, &QPushButton::clicked, this, &RankingGui::on_BackButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(RankingGuiTable);  
    layout->addWidget(backButton);    

    setLayout(layout);
}

void RankingGui::setupRankingGuiTable() {
    std::vector<std::pair<std::string, Score>> RankingGuiData = controller_->getRanking();

    RankingGuiTable->setRowCount(RankingGuiData.size());
    RankingGuiTable->setColumnCount(2);

    QStringList headers;
    headers << "Player" << "Score";
    RankingGuiTable->setHorizontalHeaderLabels(headers);

    for (size_t i = 0; i < RankingGuiData.size(); ++i) {
        QTableWidgetItem *playerItem = new QTableWidgetItem(QString::fromStdString(RankingGuiData[i].first));
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(RankingGuiData[i].second));

        RankingGuiTable->setItem(i, 0, playerItem);
        RankingGuiTable->setItem(i, 1, scoreItem);
    }

    RankingGuiTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    RankingGuiTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void RankingGui::on_BackButtonClicked() {
    emit backToMainMenu();
}
