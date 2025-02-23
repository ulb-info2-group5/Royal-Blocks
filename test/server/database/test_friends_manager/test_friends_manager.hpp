/**
 * @file test_friends_manager.hpp
 * @authors Rafaou, Ernest, Jonas
 * @brief Unit tests for FriendsManager class using CppUnit.
 */

#ifndef FRIENDS_MANAGER_TEST_HPP
#define FRIENDS_MANAGER_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../../../src/server/database/friends_manager/friends_manager.hpp"

#include <vector>

class FriendsManagerTest : public CppUnit::TestFixture {
  private:
    std::shared_ptr<DatabaseManager> dbManager;
    std::shared_ptr<FriendsManager> friendsManager;

  public:
    // Setup and teardown for the tests
    void setUp();
    void tearDown();

    // Test cases
    void testAddFriend();
    void testRemoveFriend();
    void testGetFriends();

    CPPUNIT_TEST_SUITE(FriendsManagerTest);
    CPPUNIT_TEST(testAddFriend);
    CPPUNIT_TEST(testRemoveFriend);
    CPPUNIT_TEST(testGetFriends);
    CPPUNIT_TEST_SUITE_END();
};

#endif  // TEST_FRIENDS_MANAGER_HPP
