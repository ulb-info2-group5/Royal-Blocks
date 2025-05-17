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

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <boost/asio/detail/impl/reactive_socket_service_base.ipp>
#include <boost/asio/impl/any_io_executor.ipp>
#include <boost/asio/ip/tcp.hpp>
#include <stdint.h>

class ClientManager;

namespace boost {
    namespace asio {
        class io_context;
    }
} // namespace boost

using boost::asio::ip::tcp;

/**
 * @class Network
 *
 * @brief manages new connections
 */
class Network {
  private:
    boost::asio::io_context &io_;
    tcp::acceptor acceptor_;
    ClientManager &clientManager_;

    /**
     * @brief accept new connection create a clientLink  whit the socket
     * and give the clientLink to CLientManager
     */
    void accept();

  public:
    Network(boost::asio::io_context &io, ClientManager &clientManager,
            uint16_t port);
};

#endif