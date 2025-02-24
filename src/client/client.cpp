#include "client.hpp"



using boost::asio::ip::tcp;

// ======= class tcpClient =======
// -- private --
        
void TcpClient::askForAuthentication(){
    Authentication authentication;
    std::cout << "---- authentication ----" << std::endl;
    std::cout << "pseudo : "<< std::endl;
    std::cin >> authentication.pseudo;
    std::cout << "password : " << std::endl;
    std::cin >> authentication.password;
    authentication.newCompte = true;
    sendAuthentication(authentication);
}
void TcpClient::sendAuthentication(const Authentication &authentication){
    nlohmann::json j;
    j["newCompte"] = authentication.newCompte;
    j["pseudo"] = authentication.pseudo;
    j["password"] = authentication.password;
    std::string authen; 
    buffer_.erase();
    authen = j.dump() + "\n";
    std::cout << authen << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(authen) , [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            std::cout << "--- *** authentifcation send *** ---" << std::endl; 
            this->readSocket();
        }
    });
}

void TcpClient::readSocket(){
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n', [this](boost::system::error_code ec, std::size_t length){
        if (!ec){
            std::cout << "server has been sent : " << this->buffer_ << std::endl;
            
        }
    }); 
}



void TcpClient::writeSocket(){
    std::string message = "ping \n";
    boost::asio::async_write(socket_, boost::asio::buffer(message), [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            std::cout << "--- message send ---" << std::endl; 
        }
    });
}

    
TcpClient::TcpClient(boost::asio::io_context& ioContex, const std::string& host, const std::string& port ) : socket_(ioContex) {
    tcp::resolver resolver(ioContex);
    auto endpoints = resolver.resolve(host, port);
    boost::asio::async_connect(socket_, endpoints,[this](boost::system::error_code ec, tcp::endpoint){
            if (!ec){
                std::cout << "======== conected to the server ========" << std::endl;
                //writeSocket();
                askForAuthentication();
            }
    });
}
