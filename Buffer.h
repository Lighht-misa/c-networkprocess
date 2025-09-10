#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio;
extern void use_const_buffer();
extern void use_buffer_str();
extern void use_buffer_array();
extern void wirte_to_socket(boost::asio::ip::tcp::socket& sock);