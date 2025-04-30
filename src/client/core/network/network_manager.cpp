#include "network_manager.hpp"

#include "../../../common/bindings/constants.hpp"
#include "core/server_info/server_info.hpp"

#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <sys/socket.h>

NetworkManager::NetworkManager(
    boost::asio::io_context &context,
    std::function<void(const std::string_view)> packetHandler)
    : isConnected_(false), socket_(context),
      retryTimer_(context), packetHandler_{packetHandler} {}

bool NetworkManager::connect() {
    isConnected_ = false;

    // ensure closed
    disconnect();

    boost::system::error_code addressError;
    boost::asio::ip::address address = boost::asio::ip::make_address(serverIp_, addressError);
    if (addressError) {
        return false;
    }
    boost::asio::ip::tcp::endpoint endpoint(address, serverPort_);
    boost::system::error_code ec;
    socket_.async_connect(endpoint, [this](boost::system::error_code ec) {
        if (!ec) {
            isConnected_ = true;
            receive(); // Start reading once connected
        } else {
            retry(); // Retry if connection fails
        }
    });

    return isConnected_;
}

void NetworkManager::disconnect() {
    if (socket_.is_open()) {
        boost::system::error_code ec;
        boost::system::error_code socketShutdown = socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        boost::system::error_code socketClose = socket_.close(ec);
    }

    isConnected_ = false;
}

void NetworkManager::setServerInfo(const config::ServerInfo &serverInfo) {
    if (serverInfo.ip == serverIp_ && serverInfo.port == serverPort_) {
        return;
    }

    serverPort_ = serverInfo.port;
    serverIp_ = serverInfo.ip;

    // Cancel any ongoing operations and close the socket
    boost::system::error_code ec;
    boost::system::error_code socketCancel = socket_.cancel(ec);
}

void NetworkManager::receive() {
    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(readBuf_),
        bindings::PACKET_DELIMITER,
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string_view packetView{readBuf_.data(), length - 1};
                packetHandler_(packetView);
                readBuf_.erase(0, length);
                receive(); // Continue listening for messages
            } else {
                disconnect();
                retry();
            }
        });
}

void NetworkManager::retry() {
    retryTimer_.expires_after(std::chrono::seconds(2));
    retryTimer_.async_wait([this](const boost::system::error_code &ec) {
        if (!ec) {
            connect();
        }
    });
}

void NetworkManager::start(const config::ServerInfo &serverInfo) {
    serverPort_ = serverInfo.port;
    serverIp_ = serverInfo.ip;

    connect();
}

void NetworkManager::send(const std::string &message) {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(message + std::string(bindings::PACKET_DELIMITER)),
        [](boost::system::error_code ec, size_t /*length*/) {
            if (ec) {
                std::cerr << "error while sending packet: " << ec << std::endl;
            }
        });
}

bool NetworkManager::isConnected() const { return isConnected_; }
