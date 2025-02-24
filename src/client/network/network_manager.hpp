/**
 * @file network_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Network manager class header file
 * @date 2025-02-24
 * 
 */

#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <deque>
#include <thread>

class NetworkManager {
    private:
        /*
        * @brief The io context used for asynchronous operations
        */
        boost::asio::io_context io_context_;

        /*
        * @brief The socket used to communicate with the server
        */
        boost::asio::ip::tcp::socket socket_;

        /*
        * @brief The messages to send to the server
        */
        std::deque<std::string> messagesToSend_;

        /*
        * @brief The message received from the server
        */
        std::string messageReceive_;

        /*
        * @brief The thread used to run the io context
        */
        std::thread ioThread_;

        /*
        * @brief Function to write and send messages to the server
        */
        void write();

        /*
        * @brief Function to listen and receive messages from the server
        */
        void receive();

    public:
        /*
        * @brief Construct a new Network Manager object
        */
        NetworkManager();

        /*
        * @brief Destroy the Network Manager object
        */
        ~NetworkManager();

        /*
        * @brief Connect to the server and start listening for messages
        */
        void connect();

        /*
        * @brief Disconnect from the server
        */
        void disconnect();

        /*
        * @brief Send a message to the server
        *
        * @param string message The message to send
        */
        void send(const std::string& message);
};

#endif // NETWORK_MANAGER_HPP