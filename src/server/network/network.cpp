
#include "network.hpp"



using json = nlohmann::json;


using boost::asio::ip::tcp;



// ====== Network class ======

//--- private ---
void Network::accept(){
   acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket){
    if (!ec ){
        // pls just use auto  
        std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(std::move(socket), [this](const std::string& packet){ clientManager_.handlePacket(packet); });
        newLink->start();
    }
    accept();
   });
   
}



// --- public ---
Network::Network(boost::asio::io_context& io, ClientManager &clientManager) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)), clientManager_(clientManager) {
    this->accept();
}

