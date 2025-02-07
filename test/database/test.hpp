/**
 * @file test.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Test file for the database module
 * @date 2025-02-06
 * 
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/database_manager/database_manager.hpp"

class DatabaseManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(DatabaseManagerTest);
    CPPUNIT_TEST(testCheckUserExists);
    CPPUNIT_TEST(testCheckFriendshipExists);
    CPPUNIT_TEST(testCheckUserPassword);
    CPPUNIT_TEST(testAddFriendship);
    CPPUNIT_TEST(testRemoveFriendship);
    CPPUNIT_TEST(testUpdateScore);
    CPPUNIT_TEST(testGetRanking);
    CPPUNIT_TEST(testGetFriends);
    CPPUNIT_TEST(testAddUser);
    CPPUNIT_TEST(testDeleteUser);
    CPPUNIT_TEST_SUITE_END();

    private:
        DatabaseManager *db_;

    public:
        void setUp() override;
        void tearDown() override;

        void testCreateTable();
        void testCheckUserExists();
        void testCheckFriendshipExists();
        void testCheckUserPassword();
        void testAddFriendship();
        void testRemoveFriendship();
        void testUpdateScore();
        void testGetRanking();
        void testGetFriends();
        void testAddUser();
        void testDeleteUser();
};