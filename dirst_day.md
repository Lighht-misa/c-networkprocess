#### 服务器和客户端之间的通信是如何进行的？    
  
###
**1、服务端**  
(1)服务器创建一个sockte(通信的基础)  
(2)通过bind进行绑定本地的一个端口号  
(3)用listen进行监听来电，如果有则建立链接  
(4)通过accept 再次创建一个socket进行通信
(5)通过read和write来发送接受消息  

### 
**2、客户端**  
(1)创建socket
(2)使用connect来连接服务器的ip和端口号 发起请求  
(3)wirte 和read发送接受  



### 代码实现  
**通过ip和protocl 客户端实现**  
**首先我们可以现创建一个endpoint(终端节点)**  
```cpp
int client_end_point(){
    std::string rwa_ip_address="192.168.1.34";//服务器ip
    boost::system::error_code ec;
    asio::ip::address ip_address = 
    asio::ip::address::from_string(raw_ip_address,ec);
    //asio下的from_string函数将一个单一的字符串转换为一个ip_address对象
    if(ec.value() != 0)
    {
        std::cout<<"Failed to parse the Ip address.Error Code="<< ec.value()<<"Message is" << ec.message();
        return ec.velue();
    }
    asio::ip::tcp::endpoint ep(ip_address,port_num);
    return 0;

} 
```  
#### 服务端根据本地的ip和端口本地绑定  

```cpp
int server_endpoint(){
    unsigned shor port_num=3333;//端口号
    asio::ip::address ip_address = asio::ip::address_v6::any();
    asio::ip::tcp::endpoint ep(ip_address,port_num);
    return 0;
}
```
### 为什么需要双方都建端点？
 - **如果不知道端点即使有socket这个通信技术也不知道要找谁通信**  

### 双方建立连接之后就可以进行使用socket进行通信  
**创建scoker分4步**  
（1）创建上下文  
（2）选择协议  
（3）生成socket  
（4）打开socket  
```cpp
int creat_tcp_socket(){
    asio::io_context ios;//创建上下文  
    asio::ip::tcp protocol = asio::ip::tcp::v4();//选择ipv4协议
    asio::ip::tcp::socket sock(ios);//基于上下文创建socket  
    boost::system::error_code ec;//用于记录当打开sokcet的时候的错误信息  
    sock.open(protocol,ec);//打开socket
    if(ec.velue() != 0){//if failed to open output error message
        std::cout<<"Failed to open socket!Error code is "<<ec.value()<<"Message is "<<ec.error();
        return ec.value();
    }

    return 0;
}
```

### 服务端建立一个新的accpetor的socket 因为上面的socket只是用于通信之间的 
```cpp
int crear_acceptor_socket(){
    asio::in_context ios;
    asio::ip::tcp protocol = asio::ip::tcp::v6();
    boost::system::error_code ec;
    asio::ip::tcp::acceptor acceptor(ios);
    if(ec.value() != 0){
        std::cout<<"Failed to open acceptor socket!The error is "<<ec.value()<<"Message is "<<ec.massage();
        return ec.value();
    }
    return 0;
}
```  
### 绑定acceptor  
**为什么要绑定acceptor？**  
因为是专属给服务器使用的  
  
#### ​​服务器通过 acceptor绑定到一个包含通配地址 (0.0.0.0) 和特定端口的端点，来监听所有网络接口上的连接请求。​​ 这样做既灵活又方便，是服务器编程中的常见做法。
```cpp
int bind_acceptor_socket(){
    unsigned short port_num = 3333;//假设这是我们已知服务器的端口  
    asio::ip::tcp::endoint ep(asio::ip::address_v4::any(),port_num);
    //创建一个服务区端点 接受任何类型的ipv4地址
    asio::io_context ios;
    asio::ip::tcp::acceptor acceptor(ios,ep.protocol);
    boost:;system::error_code ec();
    acceptor.bind(ec,ep.protocol());
     if(ec.value() != 0){
        std::cout<<"Failed to open acceptor socket!The error is "<<ec.value()<<"Message is "<<ec.massage();
        return ec.value();
    }
    return 0;
}

```  

### 前置条件都准备好了 当然是进行连接了！
### 客户端连接服务器
```cpp
int connect_to_end(){
    std::string raw_ip_address="192.168.1.36";
    unsigned short port_num=3333;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);//创建一个服务器端点  
    asio::io_context ios;//上下文
    asio::ip::tcp::socket sock(ios,ep.protcol());//创建一个sock连接服务器
    sock.connect(ep);//连接到ep这个端点 也就是服务器
    return 0;
}
```
### 服务器接受连接  
```cpp
int accept_new_connection(){

    const int BACKLOG_SIZE=30;//设置一个缓冲队列的大小 队满的时候不接受新的 不影响accept的

    unsigned short port_num = 333;//假设这是我们的端口号
    asio::ip::tcp::endpoint ep(asio::ip::address::any(),port_num);//创建服务器端口
    asio::io_context ios;
    asio::ip::acceptor acceptor(ios,ep.protocol());//创建一个accpetor
    acceptor.bind(ep);//将这个accpetor绑定到服务器的端口
    acceptor.listen(BACKLOG_SIZE);//开始监听
    asio::ip::tcp::socket sock(ios);
    accpetor.accept(sock)//非阻塞调用 不会死循环
    return  0;
}
```
