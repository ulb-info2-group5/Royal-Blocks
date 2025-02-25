
#include "network.hpp"



using json = nlohmann::json;


using boost::asio::ip::tcp;



// ====== Network class ======

//--- private ---
void Network::accept(){
   acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket){
    if (!ec ){
        this->waitForAuthentication(std::make_shared<tcp::socket>(std::move(socket)));
    }
    accept();
   });
   
}

bool Network::checkCredentials(std::shared_ptr<std::string> credentials){
    //for the moment just simulate a verification with the database
    std::cout << "-- ceck credentials --" << std::endl;
    return true;
}

void Network::waitForAuthentication(std::shared_ptr<tcp::socket> socket){
    auto authenticationBuffer = std::make_shared<std::string>();
    boost::asio::async_read_until(*socket, boost::asio::dynamic_buffer(*authenticationBuffer), '\n',[this, socket, authenticationBuffer](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "packet recieve :  " << *authenticationBuffer << std::endl;
        }
        if (!this->checkCredentials(authenticationBuffer)){
            this->waitForAuthentication(socket);
        }else {
            this->createNewConnection(socket);
        }
    
    });
  
}

void Network::createNewConnection(std::shared_ptr<tcp::socket> socket){
    // pls just use auto  
    std::cout << "create new connection " << std::endl;
    std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(std::move(*socket), [this](const std::string& packet){ clientManager_.handlePacket(packet); });
    newLink->start();
}





// --- public ---
Network::Network(boost::asio::io_context& io, ClientManager &clientManager) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)), clientManager_(clientManager) {
    this->accept();
}

