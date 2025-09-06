#include "endpoint.h"
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;
int client_end_point() {
    std::string raw_ip_address = "192.68.1.2";
    unsigned short port_num = 31332;
    boost::system::error_code ec;
    // 使用 make_address 替代 from_string
    asio::ip::address ip_address = asio::ip::make_address(raw_ip_address, ec);
    if (ec.value() != 0) {
        std::cout << "Faired to parest the ipaddress.Error code = " << ec.value() << ".Message is " << ec.message();
        return ec.value();
    }
    asio::ip::tcp::endpoint ep(ip_address, port_num);
    return 0;
}

 int server_end_point(){
    unsigned short port_num = 31332; // 自己的端口号 
    asio::ip::address ip_address = asio::ip::address_v6::any(); // 绑定到所有地址
    asio::ip::tcp::endpoint ep(ip_address,port_num);//生成端点进行通信  
    return 0;
 }

 int creat_tcp_socket()
 {
     //使用socket必须要求上下文环境 这是asio的要求 
     asio::io_context ioc;//生成上下文
     //创建ipv4一个协议
     asio::ip::tcp protocol = asio::ip::tcp::v4();
     asio::ip::tcp::socket sock(ioc);//上下文为ioc的一个socket
     boost::system::error_code ec;
     sock.open(protocol);//用ipve4方式 打开sokcet 进行通信
     if(ec.value() != 0){//如果ec的value为0 则说明创建失败了 打不开
        std::cout<<"Failed to open the socket.And error code = " <<ec.value()<<"Massage is "<<ec.message();
     }
     //现代boost库中 socket会自动打开 

     return 0;
 }

 int creat_acceptor_socket()
 {  
     asio::io_context ios;//生成上下文
    // asio::ip::tcp::acceptor acceptor(ios);//基于上下文进行接受新的连接  
    // asio::ip::tcp protocol = asio::ip::tcp::v4();//使用ipv4协议
    // boost::system::error_code ec;
    // acceptor.open(protocol,ec);//打开accptor
    // if(ec.value() != 0 ){
    //     std::cout<<"Failed to open the acceptor socket.And error code = " <<ec.value()<<"Message is "<<ec.message();
    // }
    //上面是旧版本的写法  
    asio::ip::tcp::acceptor a(ios,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),31332));
    //这是新版本的写法 我们在构造函数中传入了一个上下文 然后传入了一个端点，端点包含了ipv4协议和端口号
     return 0;
 }

int bind_acceptor_socket()
{
    unsigned short port_num = 31332; // 自己的端口号
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),port_num); //endpoint是一个端点 ep在构造的时候 
    //传入了一个地址和端口号 这个地址接受所有ipv4的地址
    //进行绑定 让服务器直到这个accpet是用在哪个服务上
    asio::io_context ios;//生成一个上下文  
    asio::ip::tcp::acceptor acceptor(ios,ep.protocol());//基于ios的上下文生成一个带有ep的协议的一个acceptor
    boost::system::error_code ec;
    acceptor.bind(ep,ec);//对本地任何一个地址的连接 然后进行端口号绑定 



return 0;
}

int connect_to_end() {
    // 注意：IP地址字符串中的逗号已修正为点号
    std::string raw_ip_address = "192.168.1.36";
    unsigned short port_num = 31332;
    try {
        // 使用 make_address 替代 from_string
        asio::ip::tcp::endpoint ep(asio::ip::make_address(raw_ip_address), port_num);
        asio::io_context ios;
        asio::ip::tcp::socket sock(ios, ep.protocol());
        sock.connect(ep);
    } catch (system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code() << ".Message is " << e.what();
    }
    return 0;
}
int dns_connect_to_end() {
    std::string host = "llfc.club";
    // 端口号通常使用字符串形式
    std::string port_num = "31331"; 
    asio::io_context ios;
    asio::ip::tcp::resolver resolver(ios);
    try {
        // 直接使用 resolver.resolve()，不再使用已废弃的 resolver_query
        asio::ip::tcp::resolver::iterator it = resolver.resolve(host, port_num);
        asio::ip::tcp::socket sock(ios);
        asio::connect(sock, it);
    } catch (system::system_error& e) {
        // 建议添加错误处理输出
        std::cout << "Error occured! Error code = " << e.code() << ".Message is " << e.what();
    }
    return 0;
}
int accpte_connection() {
    const int BACKLOG = 30;
    unsigned short port_num = 31332;
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
    asio::io_context ios; // 通常一个io_context足够处理服务器端socket和acceptor
    try {
        // 直接使用端点初始化acceptor，并绑定
        asio::ip::tcp::acceptor acceptor(ios, ep); 
        acceptor.listen(BACKLOG);
        asio::ip::tcp::socket sock(ios); // 使用同一个io_context
        acceptor.accept(sock);
    } catch (system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code() << ".Message is " << e.what();
    }
    return 0;
}
