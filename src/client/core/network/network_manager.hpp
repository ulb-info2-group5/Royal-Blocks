#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

class NetworkManager {
  private:
    std::string readBuf;

    /**
     * @brief The io context used for asynchronous operations
     */
    boost::asio::io_context &context_;

    /**
     * @brief The socket used to communicate with the server
     */
    boost::asio::ip::tcp::socket socket_;

    /**
     * @brief Handles the packets received by the client
     */
    std::function<void(const std::string_view)> packetHandler_;

    /**
     * @brief Function to write and send messages to the server
     */
    void write();

    /**
     * @brief Function to listen and receive messages from the server
     */
    void receive();

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
     * @brief Connect to the server and start listening for messages
     *
     * @return true if the connection was successful and false otherwise
     */
    bool connect();

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
};

#endif // NETWORK_MANAGER_HPP
