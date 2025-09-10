#include "sever.h"
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <set>
#include <exception>
using namespace boost::asio::ip;
const int max_length  = 1024;//to limit the information of biggest size
typedef std::shared_ptr<tcp::socket> socket_prt;//defined a typename
std::set<std::shared_ptr<std::thread>> thread_set;//set是一个容器 存放的是管理线程的智能指针

void session(socket_prt sock)
{

    try{
        //用for循环接受数据
        for(;;){
            char data[max_length];//设置数据最大的长度
            memset(data,'\0',max_length);
            boost::system::error_code error;
            size_t length = sock->read_some(boost::asio::buffer(data,max_length),error);
            if(error == boost::asio::error::eof){
                std::cout<<"connection closed by peer";
                break;
            }else if(error){
                throw boost::system::system_error(error);
            }
        std::cout<<"received from "<<sock->remote_endpoint().address().to_string()<<"\n";
        std::cout<<"receive message is"<<data<<"\n";
        boost::asio::write(*sock,boost::asio::buffer(data,length));
        }
    }catch(std::exception &e){

    }
}

// 这个函数根据服务器ip和端口创建一个服务器的accetpor来接受数据，用socket接受新的连接 然后为socket创建新的session
void server(boost::asio::io_context &io, unsigned short port)
{  
    tcp::acceptor ap(io,port);
    for(;;){
        socket_prt socket(new tcp::socket(io));
        ap.accept(*socket);
        auto t = std::make_shared<std::thread>(session,socket);
        thread_set.insert(t);
    }
}
