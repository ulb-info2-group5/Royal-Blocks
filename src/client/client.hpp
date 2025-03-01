#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <deque>

struct Login {
    const char type = 'C'; 
    std::string pseudo;
    std::string password;
    nlohmann::json to_json() const {
        return nlohmann::json{{"type", type}, {"pseudo", pseudo}, {"password", password}};
    }
    static Login from_json(const nlohmann::json& j){
        return Login{{j.at("type").get<const char>()},{j.at("pseudo").get<std::string>()}, {j.at("password").get<std::string>()}};
    }
};

struct Register {
    const char type ='R';
    std::string pseudo;
    std::string password;

    nlohmann::json to_json() const {
        return nlohmann::json{{"type", type}, {"pseudo", pseudo}, {"password", password}};
    }
    static Register from_json(const nlohmann::json& j){
        return Register{{j.at("type").get<const char>()},{j.at("pseudo").get<std::string>()}, {j.at("password").get<std::string>()}};
    }
};

struct Message {
    const char type = 'M';
    int receiverId;
    std::string content;

    nlohmann::json to_json() const {
        return nlohmann::json{{"type", type}, {"receiverId", receiverId}, {"content", content}};
    }
    static Message from_json(const nlohmann::json& j){
        return Message{{j.at("type").get<const char>()},{j.at("receiverId").get<int>()}, {j.at("content").get<std::string>()}};
    }
};




class TcpClient{
    private:
        boost::asio::ip::tcp::socket socket_;
        std::string buffer_;
        std::deque<std::string> writeQueue_;


        
        void sendAuthentication(const Login &authentication);
        void startRead();
        void startWrite();



        
    public: 
        TcpClient(boost::asio::io_context& ioContex, const std::string& host, const std::string& port );
        void sendMessage(const std::string& content);
        
        void askForAuthentication(); 
        void sendPackage(std::string& message);
};



#endif 