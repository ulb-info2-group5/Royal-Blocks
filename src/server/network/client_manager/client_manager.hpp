#include <boost/asio.hpp>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

// include database
#include "../../database/account_manager/account_manager.hpp"
#include "../../database/database_manager/database_manager.hpp"
#include "../../database/friends_manager/friends_manager.hpp"
#include "../../database/messages_manager/messages_manager.hpp"

#include "../../../common/bindings/authentication.hpp"
#include "../../../common/bindings/authentication_response.hpp"
#include "../../../common/bindings/binding_type.hpp"
#include "../../../common/bindings/message.hpp"
#include "../../../common/bindings/registration.hpp"
#include "../../../common/bindings/registration_response.hpp"
#include "../../../common/bindings/user_state.hpp"
#include "../../../common/bindings/user.hpp"
#include "../../server_bindings/remove_client.hpp"


#include "../matchmaking/matchmaking.hpp"

using boost::asio::ip::tcp;

class ClientLink;

// it's just a structure to bring database classes together
struct DataBase {
    std::shared_ptr<AccountManager> accountManager;
    std::shared_ptr<FriendsManager> friendsManager;
    std::shared_ptr<MessagesManager> messagesManager;
};

/*
ClientLink : Represents a single client connection. Inherits
enable_shared_from_this creates a std::shared_ptr from this to avoid premature
destruction.
*/

class ClientLink : public std::enable_shared_from_this<ClientLink> {

    using PacketHandler =
        std::function<void(const std::string &, const int clientId)>;
    using AuthPacketHandler =
        std::function<nlohmann::json(bindings::BindingType, nlohmann::json)>;
    using AuthSuccessCallback =
        std::function<void(std::shared_ptr<ClientLink>, nlohmann::json)>;

  private:
    tcp::socket socket_;
    std::string buffer_;
    boost::asio::streambuf streamBuffer_;
    
    bool mustBeDeletedFromTheWaitingForAuthList_ = false;
    bindings::State userState;

    std::optional<UserID> clientId;

    // std function to manage packages
    PacketHandler packetHandler_;
    // std function to manage authentication packages
    AuthPacketHandler authPacketHandler_;
    // callback to notify clientManager that the client is authenticated
    AuthSuccessCallback authSuccessCallback_;
    /*
     *@brief : call if client is not logged in, send package to ClientManager
     *and wait for a response
     *@param packet : string wich contains the package
     */
    void handleAuthentication(std::string &packet);

    void handleReading();
    void handleErrorReading();
    /*
     *@brief : read the socket
     */
    void read();
    /*
     *@brief : write package in the socket
     */
    void writeSocket(std::string &content);

  public:
    explicit ClientLink(tcp::socket socket, PacketHandler packetHandler,
                        AuthPacketHandler authPacketHandler,
                        AuthSuccessCallback authSuccessCallback);
    void start();

    void sendPackage(nlohmann::json gameState);

    /*
     *@brief : return true if the client is authenticated
     */
    
    bool shouldItBeDeletedFromTheList();

    void setClientId(const int id);

    void setUserState(bindings::State newState);

    bindings::State getUserState();

};

class ClientManager {
  private:
    // map => { key : client id , value : the client session }
    std::unordered_map<UserID, std::shared_ptr<ClientLink>> connectedClients_;
    std::mutex mutex_;
    DataBase database_;

    GamesManager gamesManager_;
    Matchmaking matchmaking_;

    // contains client who are not yet authenticated
    std::vector<std::shared_ptr<ClientLink>> waitingForAuthClient;
    /*
     * @brief : remove authenticated clients and clients who have closed their
     * socket from the vector waitingForAuthClient
     */
    void removeClientsFromTheWaintingList();
    /*
     * @brief : try to create a account
     * @return : true if success else false
     */
    bool attemptCreateAccount(nlohmann::json data);

    void disconnectClient(const UserID &userID);

    void removeConnection(const UserID &userID);

  public:
    ClientManager(DataBase database);
    ~ClientManager() = default;

    /*
     * @brief : call by ClientLink when the client is logged in
     * @param clientLink : shared_ptr of the clientLink
     * @param clientData : client data
     */
    void authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                         nlohmann::json clientData);


    void gameFindCallback(std::vector<PlayerID>& playersID);
    /*
     * @brief : manage of the packet received by the clientLink
     */
    void handlePacket(const std::string &packet, const UserID &clientId);

    void handlePacketMenu(const std::string &packet, const UserID &clientId);
    /*
     * @brief : manage package when the client is not yet logged in
     * @return : the response of the package
     */
    nlohmann::json authPacketHandler(bindings::BindingType type,
                                     nlohmann::json data);

    void handleMessage(nlohmann::json message);

    /*
     * @brief:  add client to the waitingForAuthCLient list
     */
    void addClientInWaitingForAuth(std::shared_ptr<ClientLink> &&clientLink);
    /*
     * @brief : add client in the unordered_map
     */
    void addConnection(std::shared_ptr<ClientLink> clientSession,
                       const std::string &pseudo);

    bool checkCredentials(nlohmann::json data);

    void updateGameStates(UserID userIds, nlohmann::json gameState);

    bool isClientConnected(UserID userId);
};