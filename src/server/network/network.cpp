
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
        nlohmann::json response;
        
        switch (type){
        case bindings::BindingType::Authentication :
            response = checkCredentials(data);
            sendResponse(socket, response);
            if (response.at("data").at("success").get<bool>()){
                this->createNewConnection(socket, data);
            }
            return;
        case bindings::BindingType::Registration :
            // TODO : create a new compte and ask for login
            break;
        default:
            break;
        }
    }
    this->waitForAuthentication(socket);
}

nlohmann::json Network::checkCredentials(nlohmann::json data){
    bindings::AuthenticationResponse response;
    std::cout << "-- check credentials --" << std::endl;
        if (clientManager_.checkCredentials(data.at("nickname").get<std::string>(), data.at("password").get<std::string>())){
            response.success = true;
            return response.to_json();
        }
    response.success = false;
    return response.to_json();
}

nlohmann::json Network::attemptToCreateAnAccount(nlohmann::json data){
    
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
    std::cout << "create new connection " << std::endl;
    // pls just use auto  
    std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(std::move(*socket), [this](const std::string& packet){ clientManager_.handlePacket(packet); });
    std::string pseudo = data.at("nickname").get<std::string>();
    clientManager_.addConnection(std::move(newLink), pseudo);
}


void Network::sendResponse(std::shared_ptr<tcp::socket> socket, nlohmann::json packet ){
    boost::asio::async_write(*socket, boost::asio::buffer(packet.dump() + "\n") , [this](boost::system::error_code ec, std::size_t){
        if (!ec){
            std::cout << "response sent ! " << std::endl;
        }
    });
}



// --- public ---
Network::Network(boost::asio::io_context& io, ClientManager &clientManager) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)), clientManager_(clientManager) {
    this->accept();
}

