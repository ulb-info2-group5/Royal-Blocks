#include "ranking.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

#include "../../core/controller/controller.hpp"

Ranking::Ranking(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {

    // Créer le tableau pour afficher le classement
    rankingTable = new QTableWidget();
    backButton = new QPushButton("Back");

    // Remplir le tableau avec les données de classement
    setupRankingTable();

    // Connecter le bouton "Back" pour revenir au menu principal
    connect(backButton, &QPushButton::clicked, this, &Ranking::on_BackButtonClicked);

    // Créer un layout pour organiser le tableau et le bouton
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(rankingTable);  // Ajouter le tableau au layout
    layout->addWidget(backButton);    // Ajouter le bouton "Back"

    // Configurer le widget avec ce layout
    setLayout(layout);
}

void Ranking::setupRankingTable() {
    // Récupérer les données du classement
    std::vector<std::pair<std::string, Score>> rankingData = controller_->getRanking();

    // Définir le nombre de lignes et de colonnes
    rankingTable->setRowCount(rankingData.size());
    rankingTable->setColumnCount(2); // Colonnes : Player, Score

    // Définir les en-têtes des colonnes
    QStringList headers;
    headers << "Player" << "Score";
    rankingTable->setHorizontalHeaderLabels(headers);

    // Remplir le tableau avec les données
    for (size_t i = 0; i < rankingData.size(); ++i) {
        QTableWidgetItem *playerItem = new QTableWidgetItem(QString::fromStdString(rankingData[i].first));
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(rankingData[i].second));

        rankingTable->setItem(i, 0, playerItem);
        rankingTable->setItem(i, 1, scoreItem);
    }

    // Ajuster la largeur des colonnes pour qu'elles prennent toute la largeur
    rankingTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    rankingTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void Ranking::on_BackButtonClicked() {
    // Retourner au menu principal (assurez-vous de connecter ce signal dans MainGui)
    emit backToMainMenu();
}
