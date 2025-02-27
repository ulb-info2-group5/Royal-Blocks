#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <sstream>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>


#include "client_manager/client_manager.hpp"

using boost::asio::ip::tcp;



class Network{
    private: 
        boost::asio::io_context& io_;
        tcp::acceptor acceptor_;
        ClientManager &clientManager_; 
        
        void waitForAuthentication(std::shared_ptr<tcp::socket> socket);
        bool checkCredentials(std::shared_ptr<std::string> credentials);
        void accept();
        void createNewConnection(std::shared_ptr<tcp::socket> socket, std::shared_ptr<std::string> credentials);
    public: 
        Network(boost::asio::io_context& io,ClientManager &clientManager );

};

#endif 