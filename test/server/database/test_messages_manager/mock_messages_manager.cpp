#include <string>
#include <vector>
#include <iostream>
#include <memory>

class MockDatabaseManager {
public:
    // Simuler l'exécution de requêtes SQL qui modifient les données
    bool executeSqlChangeData(const std::string& sql, const std::vector<std::string>& params) {
        std::cout << "Simulating SQL change: " << sql << std::endl;
        for (const auto& param : params) {
            std::cout << "Param: " << param << std::endl;
        }
        return true;  // Toujours réussi
    }

    // Simuler la récupération de données (ici, l'ID de discussion)
    bool executeSqlRecoveryInt(const std::string& sql, const std::vector<std::string>& params, int& result) {
        std::cout << "Simulating SQL recovery (int): " << sql << std::endl;
        for (const auto& param : params) {
            std::cout << "Param: " << param << std::endl;
        }
        result = 1;  // Simule une discussion existante
        return true;
    }

    // Simuler la récupération de chemin de fichier
    bool executeSqlRecoveryString(const std::string& sql, const std::vector<std::string>& params, std::string& result) {
        std::cout << "Simulating SQL recovery (string): " << sql << std::endl;
        for (const auto& param : params) {
            std::cout << "Param: " << param << std::endl;
        }
        result = "data/chat/user1_user2.json";  // Retourne un chemin fictif
        return true;
    }

    // Simuler une fonction qui créer des tables (aucune action réelle)
    void createTables(const std::string& sql) {
        std::cout << "Simulating table creation: " << sql << std::endl;
    }

    // Simuler un succès pour toutes les requêtes SQL
    void simulateSqlExecuteSuccess() {
        std::cout << "Simulating successful SQL execution" << std::endl;
    }
};
