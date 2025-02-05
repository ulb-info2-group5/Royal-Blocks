/**
 * @file account_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Account Manager class definition
 * @date 05/02/2025
 *
 */

#include "account_manager.hpp"

#include <iostream>

AccountManager::AccountManager(const string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db) << endl;
    } else {
        createTable();
    }
}

AccountManager::~AccountManager() { sqlite3_close(db); }

void AccountManager::createTable() {
    string sql = "CREATE TABLE IF NOT EXISTS users ("
                      "username TEXT PRIMARY KEY NOT NULL, "
                      "password TEXT NOT NULL)";
    executeSQL(sql);
}

bool AccountManager::executeSQL(const string &sql) {
    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error SQLite: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool AccountManager::createAccount(const string &username, const string &password) {
  string sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
  return executeSQL(sql);
}

bool AccountManager::login(const string &username, const string &password) {
    string sql = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    bool result = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return result;
}

void AccountManager::getUsers() {
  string sql = "SELECT username, password FROM users";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
      while (sqlite3_step(stmt) == SQLITE_ROW) {
          string username =
              reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
          string password =
                reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

          cout << "Username: " << username << ", Password: " << password
               << endl;
      }
      sqlite3_finalize(stmt);
  } else {
      cerr << "Erreur de lecture des utilisateurs." << endl;
  }
}

void AccountManager::launch() {

    cout << "Do you want to create an account? (y/n): ";
    char choice;
    cin >> choice;
    choice = tolower(choice);

    while (choice != 'y' && choice != 'n') {
        cout << "Invalid choice! Please enter 'y' or 'n': ";
        cin >> choice;
        choice = tolower(choice);
    }

    string username, password;

    if (choice == 'y') {
        cout << "An account will be created." << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (createAccount(username, password)) {
            cout << "Account created!" << endl;
        } else {
            cout << "Account creation failed!" << endl;
        }
    }


    cout << "You will have to login." << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    while (!login(username, password)) {
        cout << "Login failed! Please try again." << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    cout << "Login successful!" << endl;
}