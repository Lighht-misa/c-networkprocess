#include <iostream>
#include <boost/asio.hpp>
#include "synClient.h"
using namespace boost::asio::ip;

int Client_connect_endpoint()
{
    try{
        const int MAX_LENGTH = 1024;
        std::string end_point = "192.168.1.34";
        unsigned int port_num=3313;
        tcp::endpoint ep(address::from_string(end_point),port_num);
        boost::asio::io_context  ios;
        tcp::socket sock(ios);
        boost::system::error_code ec = boost::asio::error::host_not_found;
        sock.connect(ep,ec);
        if(ec)     
        {
            std::cerr<<"connect_failed!Error is "<<ec.value()<<"Message is "<<ec.message()<<"\n";
            return 0;
        }
        std::cout<<"Enter message";
        char request[MAX_LENGTH];
        std::cin.getline(request,MAX_LENGTH);
        size_t request_length = strlen(request);
        boost::asio::write(sock,boost::asio::buffer(request,request_length));
        
        char reply[MAX_LENGTH];
        size_t reply_length = boost::asio::read(sock,boost::asio::buffer(reply,request_length));
        std::cout<<"Reply is ";
        std::cout.write(reply,reply_length);
        std::cout<<"\n";
    }catch(boost::system::error_code &e){
        std::cerr<<"Error occured! Value is "<<e.value()<<"Message is "<<e.message()<<"\n";
    }
    return 0;
}
