/**
 * @file main.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Main program file
 * @date 05/02/2025
 * 
 */

#include "account_manager/account_manager.hpp"

int main() {
    AccountManager accountManager("accounts.db");
    accountManager.launch();
    accountManager.getUsers(accountManager.getDB());
    return 0;
}
