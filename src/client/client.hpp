#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

struct Authentication {
    bool newCompte; 
    std::string pseudo;
    std::string password;
};


class TcpClient{
    private:
        boost::asio::ip::tcp::socket socket_;
        std::string buffer_;
        uint8_t boolBuffer_;
        void askForAuthentication(); 
        void sendAuthentication(const Authentication &authentication);
        void readSocket();
        void writeSocket();
        void writeMessage();

        
    public: 
        TcpClient(boost::asio::io_context& ioContex, const std::string& host, const std::string& port );
};

#endif 