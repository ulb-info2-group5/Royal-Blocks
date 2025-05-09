#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <boost/asio.hpp>
#include <mutex>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <unordered_map>

#include "../account_service/account_service.hpp"
#include "../social_service/social_service.hpp"

#include "../matchmaking/matchmaking.hpp"
#include "games_manager/games_manager.hpp"

using boost::asio::ip::tcp;

class ClientLink;

// it's just a structure to bring database classes together
struct DataBase {
    std::shared_ptr<AccountManager> accountManager;
    std::shared_ptr<FriendsManager> friendsManager;
    std::shared_ptr<MessagesManager> messagesManager;
};

/**
 * @class ClientManager
 *
 * @brief handles all clients and package management
 * delegates to other services according to the package
 */
class ClientManager {
  private:
    // map => { key : client id , value : the client session }
    std::unordered_map<UserID, std::shared_ptr<ClientLink>> connectedClients_;
    std::mutex mutex_;
    AccountService accountService_;
    GamesManager gamesManager_;
    Matchmaking matchmaking_;
    SocialService socialService_;

    // contains client who are not yet authenticated
    std::vector<std::shared_ptr<ClientLink>> waitingForAuthClient;

    /**
     * @brief remove authenticated clients and clients who have closed their
     * socket from the vector waitingForAuthClient
     */
    void removeClientsFromTheWaintingList();

    /**
     * @brief  disconnects the client
     */
    void disconnectClient(const UserID &userID);

    /**
     * @brief : send the ranking to all the connected clients
     */
    void sendUpdatedRankingToClients() const;

  public:
    ClientManager(DataBase database);
    ~ClientManager() = default;

    /**
     * @brief : call by ClientLink when the client is logged in
     * @param clientLink : shared_ptr of the clientLink
     * @param clientData : client data
     */
    void authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                         nlohmann::json clientData);

    /**
     * @brief callback use by Matchmaking to notify that a party has been
     * created update the userState of all players present in the party
     * @param players : players who are present in the new game
     */
    void gameFindCallback(std::vector<Player> &players, GameMode gameMode);

    /**
     * @brief shutdown the gamesManager
     */
    void shutdown();

    /**
     * @brief delete a user from the server
     */
    void removeClient(std::optional<UserID> userID);

    /**
     * @brief : manage of the packet received by the clientLink
     */
    void handlePacket(const std::string &packet, const UserID &userID);

    /**
     * @brief manages all packets sent from the menu
     * @param packet : the packet
     * @param userID : the sender
     */
    void handlePacketMenu(const std::string &packet, const UserID &userID);

    /**
     * @brief : manage package when the client is not yet logged in
     * @return : the response of the package
     */
    std::optional<nlohmann::json> authPacketHandler(nlohmann::json binding);

    /**
     * @brief:  add client to the waitingForAuthCLient list
     */
    void addClientInWaitingForAuth(std::shared_ptr<ClientLink> &&clientLink);

    /**
     * @brief : add client in the unordered_map
     */
    void addConnection(std::shared_ptr<ClientLink> clientSession,
                       const std::string &username);

    /**
     * @brief check if  client is connected
     *
     * @return true if client is connected
     */
    bool isClientConnected(UserID userID);

    /**
     * @brief Update all menu data for a User
     * @param userID : user who will receive data
     */
    void updateMenu(UserID userID);

    /**
     * @brief update the user state to all his friends
     */
    void updateThisUserWithAllhisFriends(UserID userID);

    /**
     * @brief return the userState of a user
     */
    bindings::State getUserState(UserID userID);

    /**
     * @brief create and return a bindings::User which represents the user given
     */
    bindings::User getUser(UserID userID);
};

#endif // CLIENT_MANAGER_HPP