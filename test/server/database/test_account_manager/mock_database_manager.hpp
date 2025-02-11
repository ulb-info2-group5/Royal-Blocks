/**
 * @file mock_database_manager.hpp
 * @author Malysz Ernest
 * @date 11/02/2025
 *
 */

#ifndef MOCK_DATABASE_MANAGER_HPP
#define MOCK_DATABASE_MANAGER_HPP

#include "../../../src/server/database/database_manager/database_manager.hpp"
#include <vector>
#include <string>

class MockDatabaseManager : public DatabaseManager {
public:
    // Variables pour simuler les comportements de la base de données
    bool accountExists = false;
    bool accountDeleted = false;
    bool correctPassword = true;

    // Méthodes mockées pour simuler les comportements de la base de données
    bool executeSqlRecoveryInt(const std::string& query, const std::vector<std::string>& params, int& result) {
        if (query.find("COUNT(*) FROM users") != std::string::npos) {
            result = accountExists ? 1 : 0;
            return true;
        }
        return false;
    }

    bool executeSqlRecoveryString(const std::string& query, const std::vector<std::string>& params, std::string& result) {
        if (query.find("SELECT username") != std::string::npos) {
            result = "testUser";
            return true;
        }
        return false;
    }

    bool executeSqlChangeData(const std::string& query, const std::vector<std::string>& params) {
        if (query.find("INSERT INTO users") != std::string::npos) {
            return !accountExists; // Ne peut insérer que si l'utilisateur n'existe pas
        }
        if (query.find("DELETE FROM users") != std::string::npos) {
            accountDeleted = true;
            return true;
        }
        if (query.find("UPDATE users SET score") != std::string::npos) {
            return true;
        }
        return false;
    }

    bool createTables(const std::string& query) {
        return true;
    }
};

#endif // MOCK_DATABASE_MANAGER_HPP
