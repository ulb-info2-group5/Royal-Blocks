/**
 * @file test_friends_manager.cpp
 * @authors Rafaou, Ernest, Jonas
 * @brief Unit tests for FriendsManager class using CppUnit.
 */

#include "test_friends_manager.hpp"

void FriendsManagerTest::setUp() {
    // Initialize DatabaseManager and FriendsManager before each test case

    dbManager = std::make_shared<DatabaseManager>();
    accountManager = std::make_unique<AccountManager>(dbManager);
    friendsManager = std::make_unique<FriendsManager>(dbManager);

    accountManager->createAccount("friend1", "123");
    accountManager->createAccount("friend2", "123");
}

void FriendsManagerTest::tearDown() {
    int friend1Id = accountManager->getUserId("friend1");
    int friend2Id = accountManager->getUserId("friend2");

    accountManager->deleteAccount(friend1Id);
    accountManager->deleteAccount(friend2Id);

    // Clean up resources after each test case
    friendsManager.reset();
    dbManager.reset();
}

void FriendsManagerTest::testAddFriend() {
    /**
     * @brief Test case for adding a friend
     * Verifies that adding a friend to the database works.
     */
    int userId1 = accountManager->getUserId("friend1");
    int userId2 = accountManager->getUserId("friend2");

    bool result = friendsManager->addFriend(userId1, userId2);
    CPPUNIT_ASSERT(result);
}

void FriendsManagerTest::testRemoveFriend() {
    /**
     * @brief Test case for removing a friend
     * Verifies that removing a friend from the database works.
     */
     int userId1 = accountManager->getUserId("friend1");
     int userId2 = accountManager->getUserId("friend2");

     bool addFrienship = friendsManager->addFriend(userId1, userId2);
     CPPUNIT_ASSERT(addFrienship);
 
     bool result = friendsManager->removeFriend(userId1, userId2);
     CPPUNIT_ASSERT(result);
}

void FriendsManagerTest::testGetFriends() {
    /**
     * @brief Test case for getting a user's friends
     * Verifies if the list of friends of a user is correct.
     */

    accountManager->createAccount("user_friend_test", "123");

    int userId = accountManager->getUserId("user_friend_test");
    int friendUserId1 = accountManager->getUserId("friend1");
    int friendUserId2 = accountManager->getUserId("friend2");

    friendsManager->addFriend(userId, friendUserId1);
    friendsManager->addFriend(userId, friendUserId2);

    std::vector<int> friends = friendsManager->getFriends(userId);

    CPPUNIT_ASSERT(friends.size() == 2);
    CPPUNIT_ASSERT(friends[0] == friendUserId1 || friends[0] == friendUserId2);
    CPPUNIT_ASSERT(friends[1] == friendUserId1 || friends[1] == friendUserId2);

    // Delete the account after the test so that this account no longer exists after the test
    accountManager->deleteAccount(userId);
}
