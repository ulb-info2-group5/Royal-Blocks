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
#include <memory>

#include "../database_manager/database_manager.hpp"

using namespace std;

class AccountManager {
  private:
    shared_ptr<DatabaseManager> dbManager_;

    /*
    * @brief Check if the user already exists
    *
    * @param username Username to check
    * @return true if the user exists
    */
    bool checkUserExists(const string &username);

    /*
    * @brief Check if a friendship exists between two users
    *
    * @param user Username of the first user
    * @param friendUser Username of the second user
    * @return true if the friendship exists
    */
    bool checkFriendshipExists(const string &user, const string &friendUser);

    /*
    * @brief Check if the password is correct for a user
    *
    * @param username Username of the user
    * @param password Password to check
    * @return true if the password is correct
    */
    bool checkUserPassword(const string &username, const string &password);


  public:
    /*
    * @brief Construct a new Account Manager object
    * 
    * @param dbPath Path to the database file
    */
    AccountManager(shared_ptr<DatabaseManager> &db);

    /*
    * @brief Destroy the Account Manager object
    */
    ~AccountManager() = default;

    /*
    * @brief Create a new account
    * 
    * @param username Username of the account
    * @param password Password of the account
    * @return true if the account was created successfully
    */
    bool createAccount(const string &username, const string &password);

    /*
    * @brief Delete an account
    *
    * @param username Username of the account
    * @return true if the account was deleted successfully
    */
    bool deleteAccount(const string &username);

    /*
    * @brief Login to an account
    * 
    * @param username Username of the account
    * @param password Password of the account
    * @return true if the login was successful
    */
    bool login(const string &username, const string &password);

    /*
    * @brief Update the score of a user
    *
    * @param username Username of the user
    * @param newScore New score of the user
    */
    void updateScore(const string &username, const int newScore);

    /*
    * @brief Launch the account manager to create an account and/or login
    */
    void launch();

};

#endif // ACCOUNT_MANAGER_HPP