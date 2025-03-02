
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
        const char type =  jbuffer.at("type").get<const char>();
        switch (type){
        case CONNECTION :
            if (checkCredentials(jbuffer)){
                this->createNewConnection(socket, jbuffer);
                return;
            }
            break;
        case REGISTER :
            // TODO : create a new compte and ask for login
            break;
        default:
            break;
        }
    }
    this->waitForAuthentication(socket);
}

bool Network::checkCredentials(nlohmann::json jcredentials){
    std::cout << "-- check credentials --" << std::endl;
    //i will continue later 
        if (clientManager_.checkCredentials(jcredentials.at("pseudo").get<const std::string>(), jcredentials.at("password").get<const std::string>())){
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

void Network::createNewConnection(std::shared_ptr<tcp::socket> socket, nlohmann::json jcredentials ){
    // pls just use auto  
    std::cout << "create new connection " << std::endl;
    std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(std::move(*socket), [this](const std::string& packet){ clientManager_.handlePacket(packet); });
    std::string pseudo = jcredentials.at("pseudo").get<const std::string>();
    clientManager_.addConnection(std::move(newLink), pseudo);
    


    
}





// --- public ---
Network::Network(boost::asio::io_context& io, ClientManager &clientManager) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)), clientManager_(clientManager) {
    this->accept();
}

