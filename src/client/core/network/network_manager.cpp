#include "network_manager.hpp"

#include "../../../common/bindings/constants.hpp"

#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

// ### Public methods ###

NetworkManager::NetworkManager(
    boost::asio::io_context &context,
    std::function<void(const std::string_view)> packetHandler)
    : context_{context}, socket_(context), packetHandler_{packetHandler} {}

bool NetworkManager::connect(const std::string_view ip, uint16_t port) {
    try {
        if (socket_.is_open()) {
            boost::system::error_code ec;
            ec = socket_.close(ec);
            if (ec) {
                std::cerr << "Error while closing socket: " << ec.message()
                          << " [code: " << ec.value() << "]" << std::endl;
            } else {
                std::cout << "Socket closed successfully." << std::endl;
            }
        }

        socket_ = boost::asio::ip::tcp::socket(context_);

        boost::asio::ip::tcp::resolver resolver(context_);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(ip, std::to_string(port));
        boost::asio::connect(socket_, endpoints);

        receive(); // Start listening for messages
        return true;
    }

    catch (const std::runtime_error &e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        return false;
    }
}

void NetworkManager::disconnect() {
    if (socket_.is_open()) {
        socket_.close();
    }
}

void NetworkManager::send(const std::string &message) {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(message + std::string(bindings::PACKET_DELIMITER)),
        [](boost::system::error_code ec, std::size_t /*length*/) {
            if (ec) {
                std::cerr << "error while sending packet: " << ec << std::endl;
            }
        });
}

// ### Private methods ###

void NetworkManager::receive() {
    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(readBuf),
        bindings::PACKET_DELIMITER,
        [this](boost::system::error_code error, std::size_t length) {
            if (!error) {

                std::string_view packetView{readBuf.data(), length - 1};
                packetHandler_(packetView);
                readBuf.erase(0, length);
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
