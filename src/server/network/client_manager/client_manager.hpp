#include <unordered_map>
#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>


using boost::asio::ip::tcp;


struct FeedBack{
    bool result; 
    std::string subject;
};


/*
ClientLink : Represents a single client connection. Inherits enable_shared_from_this creates a
std::shared_ptr from this to avoid premature destruction.

use the Factory method for create a new connection by using shared_ptr
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


   
};


class ClientManager {
    private: 
        //map => { key : client id , value : the client session } 
        std::unordered_map<int , std::shared_ptr<ClientLink>> connectedClients_;
        std::mutex mutex_;

    public:
        ClientManager() = default;
        ~ClientManager() = default;
        
        void handlePacket(const std::string& packet);

        void addConnection(int clientId, std::shared_ptr<ClientLink> clientSession);
        
};