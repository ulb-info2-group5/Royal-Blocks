/**
 * @file network_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Network manager class definition file
 * @date 2025-02-24
 *
 */

#include "network_manager.hpp"
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>

// TODO: Move this to a config file ?
constexpr std::string_view PORT = "1234";
constexpr std::string_view IP = "127.0.0.1";

// ### Public methods ###

NetworkManager::NetworkManager(
    boost::asio::io_context &context,
    std::function<void(const std::string &)> packetHandler)
    : context_{context}, socket_(context), packetHandler_{packetHandler} {}

void NetworkManager::connect() {
    try {
        boost::asio::ip::tcp::resolver resolver(context_);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(IP, PORT);
        boost::asio::connect(socket_, endpoints);

        receive(); // Start listening for messages
    }

    catch (const std::exception &e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        disconnect();
        std::cout << std::endl;
        std::cerr << "Failed to connect to the server" << std::endl;
        std::exit(1); // TODO
    }
}

void NetworkManager::disconnect() {
    if (socket_.is_open()) {
        socket_.close();
    }
}

void NetworkManager::send(const std::string &message) {
    boost::asio::post(context_, [this, message]() {
        bool writing = !messagesToSend_.empty();
        messagesToSend_.push_back(message);
        if (!writing) {
            write();
        }
    });
}

// ### Private methods ###

void NetworkManager::write() {
    boost::asio::async_write(
        socket_, boost::asio::buffer(messagesToSend_.front() + "\n"),
        [this](
            boost::system::error_code error,
            std::size_t /*length*/) { // Error code and number of bytes written
            if (!error) {
                messagesToSend_.pop_front();
                if (!messagesToSend_.empty()) {
                    // write until all messages are sent
                    write();
                }
            } else {
                std::cerr << "Write error: " << error.message() << std::endl;
                // do not call disconnect here because we are already in the
                // io_thread so it will wait on the thread itself
                //
                // disconnect();
            }
        });
}

void NetworkManager::receive() {
    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(readBuf), '\n',
        [this](boost::system::error_code error, std::size_t length) {
            if (!error) {
                std::string message(
                    readBuf.substr(0, length - 1)); // Exclude '\n'
                readBuf.clear();

                packetHandler_(message);
                receive(); // Continue listening for messages
            } else {
                std::cerr << "Receive error: " << error.message() << std::endl;
                // do not call disconnect here because we are already in the
                // io_thread so it will wait on the thread itself
                //
                // disconnect();
            }
        });
}
