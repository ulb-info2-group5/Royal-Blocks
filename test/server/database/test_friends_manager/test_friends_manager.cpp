/**
 * @file test_friends_manager.cpp
 * @authors Rafaou, Ernest, Jonas
 * @brief Unit tests for FriendsManager class using CppUnit.
 */

#include "test_friends_manager.hpp"

void FriendsManagerTest::setUp() {
    // Initialize DatabaseManager and FriendsManager before each test case

    // Path correct? Or use default path?
    const std::string dbPath = "data/test.db";

    dbManager = std::make_shared<DatabaseManager>(dbPath);
    friendsManager = std::make_shared<FriendsManager>(dbManager);
}

void FriendsManagerTest::tearDown() {
    // Clean up resources after each test case
    friendsManager.reset();
    dbManager.reset();
}

void FriendsManagerTest::testAddFriend() {
    /**
     * @brief Test case for adding a friend
     * Verifies that adding a friend to the database works.
     */
    int userId = 1;
    int friendUserId = 2;

    bool result = friendsManager->addFriend(userId, friendUserId);
    CPPUNIT_ASSERT(result);
}

void FriendsManagerTest::testRemoveFriend() {
    /**
     * @brief Test case for removing a friend
     * Verifies that removing a friend from the database works.
     */
    int userId = 1;
    int friendUserId = 2;

    friendsManager->addFriend(userId, friendUserId);

    bool result = friendsManager->removeFriend(userId, friendUserId);
    CPPUNIT_ASSERT(result);
}

void FriendsManagerTest::testGetFriends() {
    /**
     * @brief Test case for getting a user's friends
     * Verifies if the list of friends of a user is correct.
     */
    int userId = 1;
    int friendUserId1 = 2;
    int friendUserId2 = 3;

    friendsManager->addFriend(userId, friendUserId1);
    friendsManager->addFriend(userId, friendUserId2);

    std::vector<int> friends = friendsManager->getFriends(userId);

    CPPUNIT_ASSERT(friends.size() == 2);
    CPPUNIT_ASSERT(friends[0] == friendUserId1 || friends[0] == friendUserId2);
    CPPUNIT_ASSERT(friends[1] == friendUserId1 || friends[1] == friendUserId2);
}
