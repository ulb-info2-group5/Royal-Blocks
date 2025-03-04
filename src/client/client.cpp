#include "client.hpp"



using boost::asio::ip::tcp;

// ======= class tcpClient =======
// -- private --
        

void TcpClient::sendAuthentication(const bindings::Authentication &authentication){
    std::string authen = authentication.to_json().dump() + "\n";
    sendPackage(authen);
}



void TcpClient::startWrite(){
    std::cout << "start Write" << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(writeQueue_.front()),[this](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            std::cout << writeQueue_.front() << std::endl;
            writeQueue_.pop_front();
            if (!writeQueue_.empty()) {
                startWrite(); 
            }
        }
    });
}

void TcpClient::startRead() {
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n',[this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Serveur: " << buffer_.substr(0, length);
                buffer_.erase(0, length);
                startRead(); 
            }
        });
}


// -- public --//

void TcpClient::sendMessage(const std::string& content){
    int receiverId  = 50;
    if (content.empty() || content == "\n") return ;
    std::string packet = bindings::Message{50, receiverId, content }.to_json().dump() + '\n';
    sendPackage(packet); 
}


void TcpClient::sendPackage(std::string& message) {
    boost::asio::post(socket_.get_executor(), [this, message]() {
            bool is_writing = !writeQueue_.empty();
            writeQueue_.push_back(message);
            if (!is_writing) {
                startWrite();
            }
        });
}

TcpClient::TcpClient(boost::asio::io_context& ioContex, const std::string& host, const std::string& port ) : socket_(ioContex) {
    tcp::resolver resolver(ioContex);
    auto endpoints = resolver.resolve(host, port);
    boost::asio::async_connect(socket_, endpoints,[this](boost::system::error_code ec, tcp::endpoint){
            if (!ec){
                std::cout << "======== conected to the server ========" << std::endl;
                this->startRead();
            }
    });
}

void TcpClient::askForAuthentication(){
    bindings::Authentication authentication;
    std::cout << "---- authentication ----" << std::endl;
    std::cout << "pseudo : "<< std::endl;
    std::cin >> authentication.nickname;
    std::cout << "password : " << std::endl;
    std::cin >> authentication.password;
    
    sendAuthentication(authentication);
}