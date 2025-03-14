/**
 * @file test_messages_manager.cpp
 * @authors: Rafaou, Ernest, Jonas
 * @brief Unit tests for MessagesManager with CppUnit.
 */

#include "test_messages_manager.hpp"
#include <memory>

/**
 * @brief Set up the test environment.
 * Called before every test case.
 */
void MessagesManagerTest::setUp() {
    // Initialize the database manager and messages manager before each test
    // case

    dbManager = std::make_shared<DatabaseManager>();
    messagesManager = std::make_unique<MessagesManager>(dbManager);
}

/**
 * @brief Tear down the test environment.
 * Called after every test case.
 */
void MessagesManagerTest::tearDown() {
    // Clean up resources after each test case
    messagesManager.reset();
    dbManager.reset();
}

/**
 * @brief Test case for adding a discussion.
 */
void MessagesManagerTest::testAddDiscussion() {
    // Test if adding a discussion between user 1 and user 2 succeeds
    bool result = messagesManager->addDiscussion(1, 2);
    CPPUNIT_ASSERT(result);
}

/**
 * @brief Test case for sending a message.
 */
void MessagesManagerTest::testSendMessage() {
    // Send a message from user 1 to user 2 and verify it is sent
    messagesManager->sendMessage(1, 2, "Hello!");

    // Retrieve the discussion and check if the message was added
    Discution discussion = messagesManager->getDiscussion(1, 2);
    CPPUNIT_ASSERT(!discussion.messages.empty());
    CPPUNIT_ASSERT_EQUAL(std::string("Hello!"),
                         discussion.messages.back().content);
}

/**
 * @brief Test case for retrieving a discussion.
 */
void MessagesManagerTest::testGetDiscussion() {
    // Send a message between user 1 and user 2
    messagesManager->sendMessage(1, 2, "Test Message");

    // Retrieve the discussion between the two users and check its properties
    Discution discussion = messagesManager->getDiscussion(1, 2);
    CPPUNIT_ASSERT_EQUAL(1, discussion.idUser1);
    CPPUNIT_ASSERT_EQUAL(2, discussion.idUser2);
    CPPUNIT_ASSERT(!discussion.messages.empty());
}
