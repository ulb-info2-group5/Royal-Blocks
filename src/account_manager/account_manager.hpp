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

    /*
      * @brief Create the users table in the database
    */
    void createTable();

  public:
    /*
      * @brief Construct a new Account Manager object
      * 
      * @param dbPath Path to the database file
    */
    AccountManager(const string &dbPath);

    /*
      * @brief Destroy the Account Manager object
    */
    ~AccountManager();

    /*
      * @brief Create a new account
      * 
      * @param username Username of the account
      * @param password Password of the account
      * @return true if the account was created successfully
    */
    bool createAccount(const string &username, const string &password);

    /*
      * @brief Login to an account
      * 
      * @param username Username of the account
      * @param password Password of the account
      * @return true if the login was successful
    */
    bool login(const string &username, const string &password);

    /*
      * @brief Launch the account manager to create an account and/or login
    */
    void launch();

    /*
      * @brief Get all users from the database
    */
    void getUsers();
};

#endif // ACCOUNT_MANAGER_HPP