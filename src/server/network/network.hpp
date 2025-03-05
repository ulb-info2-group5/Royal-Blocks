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

        /*
        * @brief : check the package received by the server and manages autentification
        * @param authenticationBuffer : buffer which contains the packet
        */
        void handleAuthentication(std::shared_ptr<tcp::socket> socket, std::shared_ptr<std::string> authenticationBuffer);

        /*
        *@brief : check account credentials  for login
        *@param data  : contains account data
        *@return : return the resonspe succeeds or faileds  
        */
        nlohmann::json checkCredentials(nlohmann::json data);

        /*
        *@brief : try to create a account 
        *@param data  : contains account data
        *@return : return the resonspe succeeds or faileds  
        */
        nlohmann::json attemptToCreateAnAccount(nlohmann::json data); 

        void accept();
        void createNewConnection(std::shared_ptr<tcp::socket> socket, nlohmann::json data);
        /*
        * @brief : send the response after a Authentication or a registration
        * @param packet : package which contains the response
        * @param socket : client socket concerned
        */
        void sendResponse(std::shared_ptr<tcp::socket> socket, nlohmann::json packet );
    public: 
        Network(boost::asio::io_context& io,ClientManager &clientManager );

};

#endif 