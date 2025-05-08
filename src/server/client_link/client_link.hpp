#ifndef CLIENT_LINK_HPP
#define CLIENT_LINK_HPP

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <optional>

#include "../../common/bindings/user_state.hpp"
#include "../../common/bindings/user.hpp"

#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"

using boost::asio::ip::tcp;

class GameServer;

/**
 * @class ClientLink
 *
 * @brief Represents a single client connection. Inherits
 * enable_shared_from_this creates a std::shared_ptr from this to avoid premature
 * destruction.
 */
class ClientLink : public std::enable_shared_from_this<ClientLink> {

    using PacketHandler =
        std::function<void(const std::string &, const int clientId)>;
    using AuthPacketHandler =
        std::function<nlohmann::json(nlohmann::json)>;
    using AuthSuccessCallback =
        std::function<void(std::shared_ptr<ClientLink>, nlohmann::json)>;

    using RemoveClientCallback = std::function<void(std::optional<UserID>)>;

  private:
    tcp::socket socket_;
    std::string buffer_;
    boost::asio::streambuf streamBuffer_;
    bool mustBeDeletedFromTheWaitingForAuthList_ = false;
    bindings::State userState;
    std::optional<UserID> clientId;
    std::optional<GameMode> gameMode_;
    std::weak_ptr<GameServer> pGame_;


    // std function to manage packages
    PacketHandler packetHandler_;
    // std function to manage authentication packages
    AuthPacketHandler authPacketHandler_;
    // callback to notify clientManager that the client is authenticated
    AuthSuccessCallback authSuccessCallback_;

    // callback to notify clientManger that the client is disconnected 
    RemoveClientCallback removeClientCallback_;

    /**
     *@brief : call if client is not logged in, send package to ClientManager
     *and wait for a response
     *@param packet : string wich contains the package
     */
    void handleAuthentication(std::string &packet);

    /**
    * @brief check the packet 
    * and gives the packet to handleAuthentication or handlePacket (clientManager) depending on the User state 
    * 
    *
    */
    void handleReading();

    /**
    * @brief handler in case of an error reading : suppress the client link 
    * with the function RemoveClientCallback
    *
    */
    void handleErrorReading();

    /**
     *@brief : read the socket
     */
    void read();

    /**
     *@brief : write package in the socket
     */
    void writeSocket(std::string &content);

    /**
    *@brief : just check if the package has a type and if it is a Json
    */
    bool checkPackage(std::string& package);

  public:
    explicit ClientLink(tcp::socket socket, PacketHandler packetHandler,
                        AuthPacketHandler authPacketHandler,
                        AuthSuccessCallback authSuccessCallback, RemoveClientCallback removeClientCallback);
    
    /**
    * @brief trigger the read on the pipeline
    */
    void start();

    /**
    * @brief write the package on the socket
    */
    void sendPackage(nlohmann::json package);
    
    /**
    * @brief reset the weak pointer of the GameServer
    */
    void resetGame();
    
    /**
    * @brief call the routine methods to correctly quit a game
    */
    void exitGame();

    /**
     *@brief : return true if the client is authenticated
     */    
    bool shouldItBeDeletedFromTheList();

    /**
    * @brief set the client id 
    */
    void setClientId(const int id);

    /**
    * @brief set the userState to the binding::state passed in parameter
    */
    void setUserState(bindings::State newState);

    /**
    * @brief set the user's gameMode to the game mode opton passed in parameter
    */
    void setGameMode(std::optional<GameMode> newGameMode);


    /**
    * @brief set the instance's attribute to the one passed in parameter for the gameServer
    */
    void jointGame(const std::weak_ptr<GameServer>& gameServer);



    /**
    * @brief returns its bindings::State
    */
    bindings::State getUserState();

    /**
    * @brief returns its GameMode
    */
    std::optional<GameMode> getGameMode();

    /**
    * @brief  returns the userID
    */
    UserID getUserID();

    /**
    * @brief returns the GameServer's weak pointer
    */
    std::weak_ptr<GameServer> getGameServer();

    

};



#endif 