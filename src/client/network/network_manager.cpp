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
    std::function<void(const std::string &)> packetHandler)
    : socket_(io_context_), packetHandler_{packetHandler} {}

NetworkManager::~NetworkManager() { disconnect(); }

void NetworkManager::connect() {
    try {
        boost::asio::ip::tcp::resolver resolver(io_context_);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(IP, PORT);
        boost::asio::connect(socket_, endpoints);

        receive(); // Start listening for messages

        ioThread_ = std::thread([this]() { io_context_.run(); });
    }

    catch (const std::exception &e) {
        std::cerr << "Connection error: " << e.what()
                  << std::endl; // TODO: check the cerr
        disconnect();
        std::cout << std::endl;
        std::cerr << "Failed to connect to the server" << std::endl;
        std::exit(1); // TODO: check the exit
    }
}

void NetworkManager::disconnect() {
    io_context_.stop();
    if (socket_.is_open()) {
        socket_.close();
    }
    if (ioThread_.joinable()) {
        ioThread_.join();
    }
}

void NetworkManager::send(const std::string &message) {
    boost::asio::post(io_context_, [this, message]() {
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
                std::cerr << "Write error: " << error.message()
                          << std::endl; // TODO: check the cerr
                disconnect();
            }
        });
}

void NetworkManager::receive() {
    std::string buf;

    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(buf),
        '\n', // TODO: check the '\n' for the end of the message
        [this, &buf](boost::system::error_code error, std::size_t length) {
            if (!error) {
                std::string message(buf.substr(0, length - 1)); // Exclude '\n'
                packetHandler_(message);
                receive(); // Continue listening for messages
            } else {
                std::cerr << "Receive error: " << error.message()
                          << std::endl; // TODO: check the cerr
                disconnect();
            }
        });
}
