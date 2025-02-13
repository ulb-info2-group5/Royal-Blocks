/**
 * @file test_account_manager.cpp
 * @author Malysz Ernest
 * @date 11/02/2025
 *
 */

#include "test_account_manager.hpp"
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

void TestAccountManager::setUp() {
    // Créer une instance de MockDatabaseManager pour chaque test
    std::shared_ptr<DatabaseManager> db = std::make_shared<MockDatabaseManager>();
    accountManager = new AccountManager(db);
}

void TestAccountManager::tearDown() {
    // Supprimer l'instance de AccountManager et MockDatabaseManager après chaque test
    delete accountManager;
    delete dbManager;
}

void TestAccountManager::testCreateAccount() {
    // Test 1 : L'utilisateur n'existe pas
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    std::string username = "testUser";
    std::string password = "testPass";
    
    // Créer un compte
    CPPUNIT_ASSERT(accountManager->createAccount(username, password));
    
    // Test 2 : L'utilisateur existe déjà
    dbManager->accountExists = true;  // Simuler que l'utilisateur existe
    CPPUNIT_ASSERT(!accountManager->createAccount(username, password));  // L'élément existe déjà, la création échoue
}

void TestAccountManager::testDeleteAccount() {
    // Test 1 : Suppression d'un compte existant
    dbManager->accountExists = true;  // L'utilisateur existe
    dbManager->accountDeleted = false;
    
    // Supprimer un compte
    CPPUNIT_ASSERT(accountManager->deleteAccount(1));  // ID utilisateur 1
    CPPUNIT_ASSERT(dbManager->accountDeleted);  // Vérifier que la suppression a été simulée

    // Test 2 : Suppression d'un compte inexistant
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    CPPUNIT_ASSERT(!accountManager->deleteAccount(1));  // La suppression échoue car l'utilisateur n'existe pas
}

void TestAccountManager::testLogin() {
    // Test 1 : Connexion réussie avec le bon nom d'utilisateur et mot de passe
    dbManager->accountExists = true;
    dbManager->correctPassword = true;
    
    std::string username = "testUser";
    std::string password = "testPass";
    
    CPPUNIT_ASSERT(accountManager->login(username, password));  // Connexion réussie

    // Test 2 : Connexion échouée avec un mot de passe incorrect
    dbManager->correctPassword = false;  // Mot de passe incorrect
    CPPUNIT_ASSERT(!accountManager->login(username, password));  // Connexion échouée

    // Test 3 : Connexion échouée avec un utilisateur inexistant
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    CPPUNIT_ASSERT(!accountManager->login(username, password));  // Connexion échouée
}

void TestAccountManager::testUpdateScore() {
    // Test 1 : Mise à jour du score avec succès
    dbManager->accountExists = true;  // L'utilisateur existe
    int userId = 1;
    int newScore = 50;
    
    // Mettre à jour le score
    CPPUNIT_ASSERT(accountManager->updateScore(userId, newScore));

    // Test 2 : Utilisateur n'existe pas, mise à jour échouée
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    CPPUNIT_ASSERT(!accountManager->updateScore(userId, newScore));  // La mise à jour échoue
}

void TestAccountManager::testGetUserId() {
    // Test 1 : Récupérer l'ID utilisateur d'un utilisateur existant
    dbManager->accountExists = true;  // L'utilisateur existe
    int userId = accountManager->getUserId("testUser");
    CPPUNIT_ASSERT(userId != -1);  // L'ID ne doit pas être -1

    // Test 2 : Utilisateur inexistant, renvoyer -1
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    userId = accountManager->getUserId("nonExistentUser");
    CPPUNIT_ASSERT(userId == -1);  // L'ID doit être -1
}

void TestAccountManager::testGetUsername() {
    // Test 1 : Récupérer le nom d'utilisateur d'un utilisateur existant
    dbManager->accountExists = true;  // L'utilisateur existe
    std::string username = accountManager->getUsername(1);
    CPPUNIT_ASSERT(username == "testUser");  // Le nom d'utilisateur doit être "testUser"

    // Test 2 : Utilisateur inexistant, renvoyer un nom vide
    dbManager->accountExists = false;  // L'utilisateur n'existe pas
    username = accountManager->getUsername(1);
    CPPUNIT_ASSERT(username.empty());  // Le nom d'utilisateur doit être vide
}
