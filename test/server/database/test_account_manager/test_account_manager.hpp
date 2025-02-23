/**
 * @file test_account_manager.hpp
 * @authors Rafaou, Ernest, Jonas
 * @brief Unit test header for AccountManager using CppUnit.
 */

#ifndef ACCOUNT_MANAGER_TEST_HPP
#define ACCOUNT_MANAGER_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <memory>
#include <string>
#include "../../../../src/server/database/account_manager/account_manager.hpp"

/**
 * @class AccountManagerTest
 * @brief Test suite for the AccountManager class.
 */
class AccountManagerTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(AccountManagerTest);
    CPPUNIT_TEST(testCreateAccount);
    CPPUNIT_TEST(testDeleteAccount);
    CPPUNIT_TEST(testLogin);
    CPPUNIT_TEST(testUpdateScore);
    CPPUNIT_TEST(testGetUserId);
    CPPUNIT_TEST(testGetUsername);
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<DatabaseManager> dbManager;
    std::shared_ptr<AccountManager> accountManager; 

public:
    /**
     * @brief Set up the test environment.
     * Called before every test case.
     */
    void setUp() override;

    /**
     * @brief Tear down the test environment.
     * Called after every test case.
     */
    void tearDown() override;

    /**
     * @brief Test case for creating an account.
     */
    void testCreateAccount();

    /**
     * @brief Test case for deleting an account.
     */
    void testDeleteAccount();

    /**
     * @brief Test case for logging in with valid credentials.
     */
    void testLogin();

    /**
     * @brief Test case for updating the score of a user.
     */
    void testUpdateScore();

    /**
     * @brief Test case for retrieving user ID by username.
     */
    void testGetUserId();

    /**
     * @brief Test case for retrieving username by user ID.
     */
    void testGetUsername();
};

#endif // TEST_ACCOUNT_MANAGER_HPP
