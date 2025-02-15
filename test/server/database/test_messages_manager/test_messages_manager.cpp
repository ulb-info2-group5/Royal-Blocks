#include "../../../src/server/database/messages_manager/messages_manager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>

// Code d'exemple avec MockDatabaseManager dans les tests
class MessagesManagerTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(MessagesManagerTest);
    
    CPPUNIT_TEST(testGenerateFileName);
    CPPUNIT_TEST(testCreateDiscussionFile);
    CPPUNIT_TEST(testAddDiscussion);
    CPPUNIT_TEST(testIsThereDiscussion);
    CPPUNIT_TEST(testGetPathDiscussion);
    CPPUNIT_TEST(testWriteMessage);
    CPPUNIT_TEST(testSendMessage);
    CPPUNIT_TEST(testGetDiscussion);
    
    CPPUNIT_TEST_SUITE_END();

private:
    shared_ptr<MockDatabaseManager> mockDbManager;
    MessagesManager* messagesManager;

public:
    void setUp() override {
        // Créer une instance de MockDatabaseManager
        mockDbManager = make_shared<MockDatabaseManager>();
        messagesManager = new MessagesManager(mockDbManager);
    }

    void tearDown() override {
        delete messagesManager;
    }

    void testGenerateFileName() {
        string expectedFileName = "data/chat/user1_user2.json";
        string actualFileName = messagesManager->generateFileName(1, 2);
        CPPUNIT_ASSERT_EQUAL(expectedFileName, actualFileName);
    }

    void testCreateDiscussionFile() {
        const string filePath = "test_discussion.json";
        Discution discussion;
        discussion.idUser1 = 1;
        discussion.idUser2 = 2;
        discussion.messages.push_back({"1", "Hello!"});
        
        bool result = messagesManager->createDiscussionFile(filePath, discussion);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT(std::filesystem::exists(filePath));

        std::filesystem::remove(filePath); // Nettoyage
    }

    void testAddDiscussion() {
        // Simuler l'exécution d'une requête SQL réussie
        mockDbManager->simulateSqlExecuteSuccess();
        
        bool result = messagesManager->addDiscussion(1, 2);
        CPPUNIT_ASSERT(result);
        
        // Vérifiez que le fichier de la discussion existe
        string filePath = messagesManager->generateFileName(1, 2);
        CPPUNIT_ASSERT(std::filesystem::exists(filePath));

        std::filesystem::remove(filePath); // Nettoyage
    }

    void testIsThereDiscussion() {
        // Simuler l'existence d'une discussion dans la base de données
        mockDbManager->simulateSqlExecuteSuccess();
        
        bool discussionExists = messagesManager->isThereDiscussion(1, 2);
        CPPUNIT_ASSERT(discussionExists);

        discussionExists = messagesManager->isThereDiscussion(2, 1);
        CPPUNIT_ASSERT(discussionExists);
    }

    void testGetPathDiscussion() {
        // Simuler la récupération du chemin de fichier dans la base de données
        string path = messagesManager->getPathDiscussion(1, 2);
        
        string expectedPath = "data/chat/user1_user2.json";
        CPPUNIT_ASSERT_EQUAL(expectedPath, path);
    }

    void testWriteMessage() {
        const string filePath = "test_write_message.json";
        Discution discussion;
        discussion.idUser1 = 1;
        discussion.idUser2 = 2;
        discussion.messages.push_back({"1", "Hello!"});
        
        messagesManager->createDiscussionFile(filePath, discussion);

        Message newMessage = {"1", "How are you?"};
        messagesManager->writeMessage(filePath, newMessage);

        Discution updatedDiscussion = messagesManager->getDiscussion(1, 2);
        CPPUNIT_ASSERT_EQUAL(size_t(2), updatedDiscussion.messages.size());

        std::filesystem::remove(filePath); // Nettoyage
    }

    void testSendMessage() {
        mockDbManager->simulateSqlExecuteSuccess();
        messagesManager->sendMessage(1, 2, "Hello!");
        
        string filePath = "data/chat/user1_user2.json";
        CPPUNIT_ASSERT(std::filesystem::exists(filePath));

        Discution discussion = messagesManager->getDiscussion(1, 2);
        CPPUNIT_ASSERT_EQUAL(size_t(1), discussion.messages.size());
        CPPUNIT_ASSERT_EQUAL(string("Hello!"), discussion.messages[0].content);

        std::filesystem::remove(filePath); // Nettoyage
    }

    void testGetDiscussion() {
        const string filePath = "test_get_discussion.json";
        Discution discussion;
        discussion.idUser1 = 1;
        discussion.idUser2 = 2;
        discussion.messages.push_back({"1", "Hello!"});
        
        messagesManager->createDiscussionFile(filePath, discussion);
        
        Discution fetchedDiscussion = messagesManager->getDiscussion(1, 2);
        CPPUNIT_ASSERT_EQUAL(size_t(1), fetchedDiscussion.messages.size());
        CPPUNIT_ASSERT_EQUAL(string("Hello!"), fetchedDiscussion.messages[0].content);

        std::filesystem::remove(filePath); // Nettoyage
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MessagesManagerTest);
