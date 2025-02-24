
#include "network.hpp"



using json = nlohmann::json;


using boost::asio::ip::tcp;


// ====== tcp connection class ======
//--- private ---
tcpConnection::tcpConnection(boost::asio::io_context& ioContext) : socket_(ioContext) {

}



void tcpConnection::readSocket(){
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n',[self = shared_from_this()](boost::system::error_code ec, std::size_t length){
        if (!ec){
            std::cout << "message recieve :  " << self->buffer_.substr(0, length) << std::endl;
            self->buffer_.erase(0, length);
        }
    });
}

void tcpConnection::writeSocket(){
    buffer_ = "ping \n";
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_), [self = shared_from_this()](boost::system::error_code ec, std::size_t){
        if (!ec){
            std::cout << "ping has been sent !" << std::endl;
        }
    });

}

void tcpConnection::waitingForAuthentication(){
    // i will replace lambda fonction by std::bind  
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n',[self = shared_from_this()](boost::system::error_code ec, std::size_t length){
        if (!ec){
            try{
                json credentials = json::parse(self->buffer_.substr(0, length));
                std::cout << " user : " << credentials["pseudo"]<< "   password : " << credentials["password"] << std::endl;
                self->buffer_.erase(0, length);
                self->sendFeedBack(true, "authentication");
            }
            catch (const std::exception& e){
                self->sendFeedBack(false, "authentication");
                std::cerr << "parsing error : " << e.what() << std::endl;
            }
        }
    });
}

void tcpConnection::sendFeedBack(bool result,const std::string& subject){
    nlohmann::json feedback;
    feedback["result"] = result;
    feedback["subject"] = subject;
    buffer_ = feedback.dump() + "\n";
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_), [self = shared_from_this()](boost::system::error_code ec, std::size_t){
        if (!ec){
            std::cout << "feedback has been sent !" << std::endl;
        }
    });



}


// --- public ---
void tcpConnection::start(){
    waitingForAuthentication();
}

tcp::socket& tcpConnection::getSocket(){
    return socket_;
}



// ====== Network class ======

//--- private ---
void Network::accept(){
    tcpConnection::pointer newConnection = tcpConnection::create(io_);
        acceptor_.async_accept(newConnection->getSocket(),[this, newConnection](boost::system::error_code ec){
                if (!ec){
                    std::cout << "====== new client connected ======" << std::endl;
                    newConnection->start();
                }
                accept();
        });
}

// --- public ---
Network::Network(boost::asio::io_context& io) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 1234)) {
    this->accept();
}




int main()
{
    try
    {
        boost::asio::io_context io_context;
        Network network(io_context);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception : " << e.what() << std::endl;
    }

    return 0;
}
