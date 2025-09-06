extern int client_end_point();//客户端创建一个端点
extern int server_end_point();//服务端创建一个端点
extern int creat_tcp_socket();//创建sokcet通信  //创建完双方的端点之后 创建socket进行通信  
extern int creat_acceptor_socket();//创建一个服务端的socket 用于接收请求  
extern int bind_acceptor_socket();//创建服务端的绑定函数 在客户端发送请求的时候 服务器绑定客户端的socket
extern int connect_to_end();//直到上一步为止 服务器和客户端都创建了端点、socket、绑定了socket  现在客户端要连接服务器
extern int dns_connect_to_end();//使用域名连接服务器
extern int accpte_connection();//服务器接受客户端的连接请求