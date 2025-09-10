#include <memory>
#include <boost/asio.hpp>
using namespace boost::asio::ip;
typedef std::shared_ptr<tcp::socket> socket_prt;
extern void session(socket_prt socket);
extern void server(boost::asio::io_context &io,unsigned short port);