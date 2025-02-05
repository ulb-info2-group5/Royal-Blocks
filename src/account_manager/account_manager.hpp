/**
 * @file account_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Account Manager class definition
 * @date 05/02/2025
 *
 */

#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP

#include <string>
#include <sqlite3.h>

using namespace std;

class AccountManager {
  private:
    sqlite3 *db;
    bool executeSQL(const string &sql);
    void createTable();

  public:
    AccountManager(const string &dbPath);
    ~AccountManager();
    sqlite3 *getDB();
    bool createAccount(const string &username, const string &password);
    bool login(const string &username, const string &password);
    void getUsers(sqlite3 *db);
    void launch();
};

#endif // ACCOUNT_MANAGER_HPP