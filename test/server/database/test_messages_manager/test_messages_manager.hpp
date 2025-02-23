/**
 * @file test_messages_manager.hpp
 * @authors: Rafaou, Ernest, Jonas
 * @brief Unit test header for MessagesManager using CppUnit.
 */

#ifndef MESSAGES_MANAGER_TEST_HPP
#define MESSAGES_MANAGER_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "../../../../src/server/database/messages_manager/messages_manager.hpp"
#include <memory>

class MessagesManagerTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MessagesManagerTest);
    CPPUNIT_TEST(testAddDiscussion);
    CPPUNIT_TEST(testSendMessage);
    CPPUNIT_TEST(testGetDiscussion);
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<DatabaseManager> dbManager;
    std::shared_ptr<MessagesManager> messagesManager;

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
     * @brief Test case for adding a discussion.
     */
    void testAddDiscussion();

    /**
     * @brief Test case for sending a message.
     */
    void testSendMessage();

    /**
     * @brief Test case for retrieving a discussion.
     */
    void testGetDiscussion();
};

#endif // TEST_MESSAGES_MANAGER_HPP
