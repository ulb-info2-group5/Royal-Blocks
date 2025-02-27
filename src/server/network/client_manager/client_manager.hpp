#include <unordered_map>
#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

//include database
#include "../../database/database_manager/database_manager.hpp"
#include "../../database/account_manager/account_manager.hpp"
#include "../../database/friends_manager/friends_manager.hpp"
#include "../../database/messages_manager/messages_manager.hpp"


using boost::asio::ip::tcp;


enum PacketType :char {
    MESSAGE = 'M',
    CONNECTION = 'C',
    DECONNECTION = 'D'
};

struct FeedBack{
    bool result; 
    std::string subject;
};

//it's just a structure to bring database classes together
struct DataBase{
    std::shared_ptr<AccountManager> accountManager;
    std::shared_ptr<FriendsManager> friendsManager;
    std::shared_ptr<MessagesManager> messagesManager;
};


/*
ClientLink : Represents a single client connection. Inherits enable_shared_from_this creates a
std::shared_ptr from this to avoid premature destruction.
*/

class ClientLink : public std::enable_shared_from_this<ClientLink>{
    private: 
        tcp::socket socket_;
        std::string buffer_;
        std::function<void (const std::string& )> packetHandler_;
        void read();

        

    public :
        explicit ClientLink(tcp::socket socket, std::function<void (const std::string& )> packetHandler);
        ClientLink(ClientLink && other) = default;
        ClientLink& operator=(ClientLink&& other) =  default;
        void start();
        void recieveMessage(const int &senderId , const std::string & content );


   
};


class ClientManager {
    private: 
        //map => { key : client id , value : the client session } 
        std::unordered_map<int , std::shared_ptr<ClientLink>> connectedClients_;
        std::mutex mutex_;
        DataBase database_;

    public:
        ClientManager(DataBase database);
        ~ClientManager() = default;
        
        void handlePacket(const std::string& packet);
        void handleMessage(nlohmann::json message);

        void addConnection(std::shared_ptr<ClientLink> clientSession, const std::string& pseudo);
        void removeConnection(const int & clientId);
        bool checkCredentials(const std::string& pseudo, const std::string& password);
};