#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <stdint.h>
#include <boost/asio/ip/tcp.hpp>                // pour tcp
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/detail/impl/epoll_reactor.hpp>
#include <boost/asio/detail/impl/reactive_socket_service_base.ipp>
#include <boost/asio/impl/any_io_executor.ipp>
#include <chrono>
#include <functional>
#include <string>
#include <string_view>

namespace boost { namespace asio { class io_context; } }
namespace config { struct ServerInfo; }


class NetworkManager {
  private:
    bool isConnected_;

    /**
     * @brief The socket used to communicate with the server
     */
    boost::asio::ip::tcp::socket socket_;

    std::string serverIp_;
    uint16_t serverPort_;

    std::string readBuf_;

    boost::asio::steady_timer retryTimer_;

    /**
     * @brief function to be called when the client is disconnected from the server
     */
    std::function<void()> disconnectHandler_;

    /**
     * @brief Handles the packets received by the client
     */
    std::function<void(const std::string_view)> packetHandler_;

    /**
     * @brief Connect to the server and start listening for messages
     *
     * @return true if the connection was successful and false otherwise
     */
    bool connect();

    /**
     * @brief Function to write and send messages to the server
     */
    void write();

    /**
     * @brief Function to listen and receive messages from the server
     */
    void receive();

    /**
     * @brief Attempt to connect again.
     */
    void retry();

  public:
    /**
     * @brief Construct a new Network Manager object
     */
    NetworkManager(boost::asio::io_context &context,
                   std::function<void(const std::string_view)> packetHandler);

    /**
     * @brief Destroy the Network Manager object
     */
    ~NetworkManager() = default;

    /**
     * @brief Sets the server info, will reattempt a new connection
     * automatically.
     */
    void setServerInfo(const config::ServerInfo &serverInfo);

    /**
     * @brief Connects and starts listening for packets.
     */
    void start(const config::ServerInfo &serverInfo);

    /**
     * @brief Disconnect from the server
     */
    void disconnect();

    /**
     * @brief Send a message to the server
     *
     * @param string message The message to send
     */
    void send(const std::string &message);

    /**
     * @brief Returns whether the client is connected to the configured server.
     */
    bool isConnected() const;

    /**
     * @brief Sets the function to be called when the client is disconnected
     *
     * @param handler The function to be called
     */
    void setDisconnectHandler(const std::function<void()> handler);
};

#endif // NETWORK_MANAGER_HPP
