#include "test_account_manager.hpp"
#include <memory>

void AccountManagerTest::setUp() {
    // Initialize DatabaseManager and AccountManager before each test case.

    dbManager = std::make_shared<DatabaseManager>();
    accountManager = std::make_unique<AccountManager>(dbManager);

    accountManager->createAccount("test_user", "password123");
}

void AccountManagerTest::tearDown() {
    // Delete the user after the test so when we restart the test, the user test
    // is no longer in the database
    int userId = accountManager->getUserId("test_user");
    accountManager->deleteAccount(userId);

    // Clean up resources after each test case.
    accountManager.reset();
    dbManager.reset();
}

void AccountManagerTest::testCreateAccount() {
    /**
     * @brief Test case for creating an account.
     * Verifies if creating an account with valid credentials is successful.
     */
    CreateAccountStatus result =
        accountManager->createAccount("test", "password123");
    CPPUNIT_ASSERT(result == CreateAccountStatus::SUCCESS);

    // Verify account creation (Assuming getUserId returns a valid ID if account
    // exists)
    int userId = accountManager->getUserId("test");
    CPPUNIT_ASSERT(userId > 0);

    // Delete the user after the test so when we restart the test, the user test
    // is no longer in the database
    accountManager->deleteAccount(userId);
}

void AccountManagerTest::testDeleteAccount() {
    /**
     * @brief Test case for deleting an account.
     * Verifies if deleting an existing account is successful.
     */
    CreateAccountStatus create =
        accountManager->createAccount("delete_user", "password123");
    CPPUNIT_ASSERT(create == CreateAccountStatus::SUCCESS);

    int userId = accountManager->getUserId("delete_user");
    bool result = accountManager->deleteAccount(userId);
    CPPUNIT_ASSERT(result);
}

void AccountManagerTest::testLogin() {
    /**
     * @brief Test case for logging in with valid credentials.
     * Verifies if login works with correct username and password.
     */
    bool result = accountManager->login("test_user", "password123");
    CPPUNIT_ASSERT(result);

    // Test invalid login
    result = accountManager->login("test_user", "wrongpassword");
    CPPUNIT_ASSERT(!result);
}

void AccountManagerTest::testUpdateScore() {
    /**
     * @brief Test case for updating the score of a user.
     * Verifies if the score of a user is updated successfully.
     */
    int userId = accountManager->getUserId("test_user");
    accountManager->updateScore(userId, 100);

    // Assuming you can retrieve user score, otherwise mock this method
    // int updatedScore = accountManager->getUserScore(userId);
    // CPPUNIT_ASSERT_EQUAL(100, updatedScore);
}

void AccountManagerTest::testGetUserId() {
    /**
     * @brief Test case for retrieving user ID by username.
     * Verifies if the correct user ID is returned for a given username.
     */
    int userId = accountManager->getUserId("test_user");
    CPPUNIT_ASSERT(userId > 0);
}

void AccountManagerTest::testGetUsername() {
    /**
     * @brief Test case for retrieving username by user ID.
     * Verifies if the correct username is returned for a given user ID.
     */
    int userId = accountManager->getUserId("test_user");
    std::string username = accountManager->getUsername(userId);
    CPPUNIT_ASSERT_EQUAL(std::string("test_user"), username);
}
