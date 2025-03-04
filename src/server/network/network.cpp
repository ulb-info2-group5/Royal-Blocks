
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


void Network::handleAuthentication(std::shared_ptr<tcp::socket> socket, std::shared_ptr<std::string> authenticationBuffer){
    if (!(*authenticationBuffer).empty()){
        nlohmann::json jbuffer =  nlohmann::json::parse(*authenticationBuffer);
        std::cout << *authenticationBuffer <<std::endl;
        bindings::BindingType type =  jbuffer.at("type").get<bindings::BindingType>();
        nlohmann::json data = jbuffer.at("data").get<nlohmann::json>();
        switch (type){
        case bindings::BindingType::Authentication :
            if (checkCredentials(data)){
                this->createNewConnection(socket, data);
                return;
            }
            break;
        case bindings::BindingType::Registration :
            // TODO : create a new compte and ask for login
            break;
        default:
            break;
        }
    }
    this->waitForAuthentication(socket);
}

bool Network::checkCredentials(nlohmann::json data){
    std::cout << "-- check credentials --" << std::endl;
        if (clientManager_.checkCredentials(data.at("nickname").get<std::string>(), data.at("password").get<std::string>())){
            return true;
        }
    
    return false;
}

void Network::waitForAuthentication(std::shared_ptr<tcp::socket> socket){
    auto authenticationBuffer = std::make_shared<std::string>();
    boost::asio::async_read_until(*socket, boost::asio::dynamic_buffer(*authenticationBuffer), '\n',[this, socket, authenticationBuffer](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "packet recieve :  " << *authenticationBuffer << std::endl;
            this->handleAuthentication(socket, authenticationBuffer);
        }
        
    
    });
  
}

void Network::createNewConnection(std::shared_ptr<tcp::socket> socket, nlohmann::json data ){
    // pls just use auto  
    std::cout << "create new connection " << std::endl;
    std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(std::move(*socket), [this](const std::string& packet){ clientManager_.handlePacket(packet); });
    std::string pseudo = data.at("nickname").get<std::string>();
    clientManager_.addConnection(std::move(newLink), pseudo);
    


    
}





// --- public ---
Network::Network(boost::asio::io_context& io, ClientManager &clientManager) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)), clientManager_(clientManager) {
    this->accept();
}

