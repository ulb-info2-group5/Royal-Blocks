#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <stdint.h>
#include <boost/asio/detail/impl/reactive_socket_service_base.ipp>
#include <boost/asio/impl/any_io_executor.ipp>
#include <boost/asio/ip/tcp.hpp>

class ClientManager;

namespace boost { namespace asio { class io_context; } }

using boost::asio::ip::tcp;

/**
 * @class
 *
 * @brief
 */
class Network {
  private:
    boost::asio::io_context &io_;
    tcp::acceptor acceptor_;
    ClientManager &clientManager_;

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void accept();

  public:
    Network(boost::asio::io_context &io, ClientManager &clientManager, uint16_t port);
};

#endif