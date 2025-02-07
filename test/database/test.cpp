/**
 * @file test.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Test file for the database module
 * @date 2025-02-06
 * 
 */

#include "test.hpp"
#include <cppunit/TestAssert.h>


void DatabaseManagerTest::setUp() {
    db_ = new DatabaseManager();
}

void DatabaseManagerTest::tearDown() {
    delete db_;
}

void DatabaseManagerTest::testAddUser() {
    CPPUNIT_ASSERT(db_->addUser("User", "password123"));
}

void DatabaseManagerTest::testCheckUserExists() {
    db_->addUser("User", "pass");
    CPPUNIT_ASSERT(db_->checkUserExists("User"));
    CPPUNIT_ASSERT(!db_->checkUserExists("nonExistingUser"));
}

void DatabaseManagerTest::testCheckUserPassword() {
    db_->addUser("user1", "securePass");
    CPPUNIT_ASSERT(db_->checkUserPassword("user1", "securePass"));
    CPPUNIT_ASSERT(!db_->checkUserPassword("user1", "wrongPass"));
}

void DatabaseManagerTest::testDeleteUser() {
    db_->addUser("deleteUser", "123");
    CPPUNIT_ASSERT(db_->deleteUser("deleteUser"));
    CPPUNIT_ASSERT(!db_->checkUserExists("deleteUser"));
}

void DatabaseManagerTest::testAddFriendship() {
    db_->addUser("Alice", "pass");
    db_->addUser("Bob", "pass");
    CPPUNIT_ASSERT(db_->addFriendshipDatabase("Alice", "Bob"));
}

void DatabaseManagerTest::testCheckFriendshipExists() {
    db_->addUser("Charlie", "pass");
    db_->addUser("David", "pass");
    db_->addUser("Alice", "pass");
    db_->addFriendshipDatabase("Charlie", "David");
    CPPUNIT_ASSERT(db_->checkFriendshipExists("Charlie", "David"));
    CPPUNIT_ASSERT(!db_->checkFriendshipExists("Charlie", "Alice"));
    CPPUNIT_ASSERT(!db_->checkFriendshipExists("Charlie", "Eve"));
}

void DatabaseManagerTest::testRemoveFriendship() {
    db_->addUser("Eve", "pass");
    db_->addUser("Frank", "pass");
    db_->addFriendshipDatabase("Eve", "Frank");
    CPPUNIT_ASSERT(db_->removeFriendshipDatabase("Eve", "Frank"));
    CPPUNIT_ASSERT(!db_->checkFriendshipExists("Eve", "Frank"));
}

void DatabaseManagerTest::testUpdateScore() {
    db_->addUser("Gamer", "pass");
    db_->updateScoreDatabase("Gamer", 50);
    vector<pair<string, int>> ranking = db_->getRanking();
    CPPUNIT_ASSERT(!ranking.empty());
    CPPUNIT_ASSERT_EQUAL(50, ranking[0].second);
}

void DatabaseManagerTest::testGetRanking() {
    db_->addUser("Player1", "pass");
    db_->addUser("Player2", "pass");
    db_->updateScoreDatabase("Player1", 100);
    db_->updateScoreDatabase("Player2", 200);
    vector<pair<string, int>> ranking = db_->getRanking();
    CPPUNIT_ASSERT(!ranking.empty());
    CPPUNIT_ASSERT_EQUAL(string("Player2"), ranking[0].first);
}

void DatabaseManagerTest::testGetFriends() {
    db_->addUser("Alice", "pass");
    db_->addUser("Bob", "pass");
    db_->addFriendshipDatabase("Alice", "Bob");
    vector<string> friends = db_->getFriends("Alice");
    CPPUNIT_ASSERT_EQUAL(size_t(1), friends.size());
    CPPUNIT_ASSERT_EQUAL(string("Y"), friends[0]);
}

CPPUNIT_TEST_SUITE_REGISTRATION(DatabaseManagerTest);
