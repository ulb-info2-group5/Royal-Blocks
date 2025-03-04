#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <deque>
#include "../common/bindings/authentication.hpp"
#include "../common/bindings/authentication_response.hpp"
#include "../common/bindings/message.hpp"
#include "../common/bindings/registration.hpp"
#include "../common/bindings/registration_response.hpp"


class TcpClient{
    private:
        boost::asio::ip::tcp::socket socket_;
        std::string buffer_;
        std::deque<std::string> writeQueue_;


        
        void sendAuthentication(const bindings::Authentication& authentication);
        void startRead();
        void startWrite();



        
    public: 
        TcpClient(boost::asio::io_context& ioContex, const std::string& host, const std::string& port );
        void sendMessage(const std::string& content);
        
        void askForAuthentication(); 
        void sendPackage(std::string& message);
};



#endif 