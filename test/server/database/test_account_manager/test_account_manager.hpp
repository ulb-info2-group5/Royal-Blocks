/**
 * @file test_account_manager.hpp
 * @author Malysz Ernest
 * @date 11/02/2025
 *
 */

#ifndef TEST_ACCOUNT_MANAGER_HPP
#define TEST_ACCOUNT_MANAGER_HPP

#include <cppunit/extensions/HelperMacros.h>
#include "mock_database_manager.hpp"
#include "../../../src/server/database/account_manager/account_manager.hpp"

class TestAccountManager : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestAccountManager);
    CPPUNIT_TEST(testCreateAccount);      // Tester la création d'un compte
    CPPUNIT_TEST(testDeleteAccount);      // Tester la suppression d'un compte
    CPPUNIT_TEST(testLogin);              // Tester la connexion d'un utilisateur
    CPPUNIT_TEST(testUpdateScore);        // Tester la mise à jour du score
    CPPUNIT_TEST(testGetUserId);          // Tester la récupération de l'ID utilisateur
    CPPUNIT_TEST(testGetUsername);        // Tester la récupération du nom d'utilisateur
    CPPUNIT_TEST_SUITE_END();

public:
    // Méthodes de test
    void setUp() override;
    void tearDown() override;

    void testCreateAccount();
    void testDeleteAccount();
    void testLogin();
    void testUpdateScore();
    void testGetUserId();
    void testGetUsername();

private:
    MockDatabaseManager* dbManager;      // Pointeur vers la base de données simulée
    AccountManager* accountManager;      // Pointeur vers l'objet AccountManager à tester
};

#endif // TEST_ACCOUNT_MANAGER_HPP
