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

#include "../../../common/bindings/authentication.hpp"
#include "../../../common/bindings/authentication_response.hpp"
#include "../../../common/bindings/message.hpp"
#include "../../../common/bindings/registration.hpp"
#include "../../../common/bindings/registration_response.hpp"
#include "../../../common/bindings/binding_type.hpp"

using boost::asio::ip::tcp;



class ClientLink;

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
    using PacketHandler = std::function<void (const std::string& )>;
    using AuthPacketHandler  = std::function<nlohmann::json (bindings::BindingType , nlohmann::json)>;
    using AuthSuccessCallback = std::function<void(std::shared_ptr<ClientLink>, nlohmann::json)>;

    private: 
        tcp::socket socket_;
        std::string buffer_;
        boost::asio::streambuf streamBuffer_;
        bool identify_ = false;
        PacketHandler packetHandler_;
        AuthPacketHandler authPacketHandler_;
        AuthSuccessCallback authSuccessCallback_;
        void waitForAuthentication();
        void handleAuthentication(std::string & packet);
        void read();
        void writeSocket(std::string& content);
    

   
    public :
       
        explicit ClientLink(tcp::socket socket, PacketHandler packetHandler, AuthPacketHandler authPacketHandler, AuthSuccessCallback authSuccessCallback);

        void sendResponse(nlohmann::json response);
        void start();
        void recieveMessage(const std::string & content );
        bool isIdentify();


    
};


class ClientManager {
    private: 
        //map => { key : client id , value : the client session } 
        std::unordered_map<int , std::shared_ptr<ClientLink>> connectedClients_;
        std::mutex mutex_;
        DataBase database_;
        std::vector<std::shared_ptr<ClientLink>> waitingForAuthClient;

        void updateWaitingClient();

    public:
        ClientManager(DataBase database);
        ~ClientManager() = default;
        

        void authSuccessCall(std::shared_ptr<ClientLink> clientLink, nlohmann::json clientData);
        void handlePacket(const std::string& packet);
        nlohmann::json authPacketHandler(bindings::BindingType type, nlohmann::json data);

        void handleMessage(nlohmann::json message);
        
        void addClientInWaitingForAuth(std::shared_ptr<ClientLink> clientLink);

        void addConnection(std::shared_ptr<ClientLink> clientSession, const std::string& pseudo);

        void removeConnection(const int & clientId);
        bool checkCredentials(nlohmann::json data);
};