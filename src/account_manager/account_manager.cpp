/**
 * @file account_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Account Manager class definition
 * @date 05/02/2025
 *
 */

#include "account_manager.hpp"
#include "../common/sql_functions.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// TODO: create class for DatabaseManager to have just the dateBase to do there

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
                 "password TEXT NOT NULL, "
                 "score INTEGER DEFAULT 0)";
    executeSQL(db,sql);
}

bool AccountManager::createAccount(const string &username,
                                   const string &password) {    
    // Check if the username already exist
    if (userExists(db, username)) {
        cerr << "Error: User '" << username << "' already exist." << endl;
        return false;
    }
  
    string sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
    return executeSQL(db, sql);
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

// TODO: maybe remove it
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
      cerr << "User reading error." << endl;
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
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        while (!createAccount(username, password)) {
            cout << "Enter a username: ";
            cin >> username;
            cout << "Enter a password: ";
            cin >> password;
        }
            
        cout << "Account created!" << endl;
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

vector<pair<string, int>> AccountManager::getRanking() const {
    vector<pair<string, int>> ranking;

    string sql = "SELECT username, score FROM users ORDER BY score DESC";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            string username =
                reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            int score = sqlite3_column_int(stmt, 1);

            ranking.push_back({username, score});
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error in getting ranking." << endl;
    }

    return ranking;
}

// TODO: keep it there or in a new class ?
void AccountManager::updateScore(const string &username, const int newScore) {
    updateScoreDatabase(db, username, newScore);
}