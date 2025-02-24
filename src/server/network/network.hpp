#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <sstream>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using boost::asio::ip::tcp;

struct FeedBack{
    bool result; 
    std::string subject;
};



/*
tcpConnection : Represents a single client connection. Inherits enable_shared_from_this creates a
std::shared_ptr from this to avoid premature destruction.

use the Factory method for create a new connection by using shared_ptr
*/

class tcpConnection : public std::enable_shared_from_this<tcpConnection>{
    private: 
        tcp::socket socket_;
        std::string buffer_;

        tcpConnection(boost::asio::io_context& ioContext);

        void writeSocket();
        void readSocket();

        /*
        * @brief sends feedback when the client does an operation like ask for ahthentication
        * 
        * @param result : true if the operation went well or else it's false
        * 
        * @param subject : subject of the feedback   
        */
        void sendFeedBack(bool result,const std::string& subject);
        /*
        *@brief read in the client socket until the client send his credential
        */
        void waitingForAuthentication();

    public: 
        typedef std::shared_ptr<tcpConnection> pointer;

        static pointer create(boost::asio::io_context& ioContext){
            return pointer(new tcpConnection(ioContext));
        }

        void start();

        tcp::socket& getSocket();

};


class Network{
    private: 
    
        boost::asio::io_context& io_;
        tcp::acceptor acceptor_;

        void accept();
    public: 
        Network(boost::asio::io_context& io);

};

#endif 