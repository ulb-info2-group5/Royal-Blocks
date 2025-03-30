#include <boost/asio.hpp>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "../social_service/social_service.hpp"



#include "../matchmaking/matchmaking.hpp"

using boost::asio::ip::tcp;

class ClientLink;

// it's just a structure to bring database classes together
struct DataBase {
    std::shared_ptr<AccountManager> accountManager;
    std::shared_ptr<FriendsManager> friendsManager;
    std::shared_ptr<MessagesManager> messagesManager;
};


class ClientManager {
  private:
    // map => { key : client id , value : the client session }
    std::unordered_map<UserID, std::shared_ptr<ClientLink>> connectedClients_;
    std::mutex mutex_;
    DataBase database_;

    GamesManager gamesManager_;
    Matchmaking matchmaking_;
    SocialService socialService_;


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

    /*
    * @brief : send the ranking to all the connected clients
    */
    void sendUpdatedRankingToClients() const;


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


    void gameFindCallback(std::vector<Player>& players, GameMode gameMode);
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

    void updateGamePlayer(UserID userIds, nlohmann::json gameState);

    bool isClientConnected(UserID userId);

    void updateMenu(UserID userId );

    void updateThisUserWithAllhisFriends(UserID userId); 
    
    bindings::State getUserState(UserID userID);

    bindings::User getUser(UserID userID);


};