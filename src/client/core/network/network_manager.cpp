/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "network_manager.hpp"

#include "../../../common/bindings/constants.hpp"
#include "core/server_info/server_info.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <new>
#include <string>
#include <utility>

constexpr std::chrono::milliseconds TIME_BTWN_RETRIES(100);

NetworkManager::NetworkManager(
    asio::io_context &context,
    std::function<void(const std::string_view)> packetHandler)
    : isConnected_(false), socket_(context), retryTimer_(context),
      packetHandler_{packetHandler} {}

bool NetworkManager::connect() {
    // ensure closed
    disconnect();

    asio::error_code addressError;
    asio::ip::address address =
        asio::ip::make_address(serverIp_, addressError);
    if (addressError) {
        return false;
    }
    asio::ip::tcp::endpoint endpoint(address, serverPort_);
    socket_.async_connect(endpoint, [this](asio::error_code ec) {
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
    if (socket_.is_open() && isConnected_) {
        asio::error_code ec;
        asio::error_code socketShutdown =
            socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        if (socketShutdown) {
            std::cerr << "Error shutting down socket: "
                      << socketShutdown.message() << std::endl;
        }
        asio::error_code socketClose = socket_.close(ec);
        if (socketClose) {
            std::cerr << "Error closing socket: " << socketClose.message()
                      << std::endl;
        }
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
    asio::error_code ec;
    asio::error_code socketCancel = socket_.cancel(ec);
    if (socketCancel) {
        std::cerr << "Error cancelling socket: " << socketCancel.message()
                  << std::endl;
    }
}

void NetworkManager::receive() {
    asio::async_read_until(
        socket_, asio::dynamic_buffer(readBuf_),
        bindings::PACKET_DELIMITER,
        [this](asio::error_code ec, std::size_t length) {
            if (!ec) {
                std::string_view packetView{readBuf_.data(), length - 1};
                packetHandler_(packetView);
                readBuf_.erase(0, length);
                receive(); // Continue listening for messages
            } else {
                disconnect();
                if (disconnectHandler_) {
                    disconnectHandler_();
                }
                retry();
            }
        });
}

void NetworkManager::retry() {
    retryTimer_.expires_after(TIME_BTWN_RETRIES);
    retryTimer_.async_wait([this](const asio::error_code &ec) {
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
    asio::async_write(
        socket_,
        asio::buffer(message + std::string(bindings::PACKET_DELIMITER)),
        [](asio::error_code ec, size_t /*length*/) {
            if (ec) {
                std::cerr << "error while sending packet: " << ec << std::endl;
            }
        });
}

bool NetworkManager::isConnected() const { return isConnected_; }

void NetworkManager::setDisconnectHandler(const std::function<void()> handler) {
    disconnectHandler_ = handler;
}
