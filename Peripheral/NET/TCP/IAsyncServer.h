#ifndef IASYNCSERVER_H
#define IASYNCSERVER_H


#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/generic/detail/endpoint.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>


namespace NET {
namespace TCP {

class IAsyncServer
{

public:

   virtual void init() = 0;
   virtual bool start() = 0;
   virtual bool stop()= 0;
   virtual bool is_running() const = 0;
   virtual void send(const char * data, size_t size , std::string client_id)= 0;
   virtual boost::signals2::connection connect_on_client_connected(std::function<void(std::string ip, std::string port, std::string client_id)> func)= 0;
   virtual boost::signals2::connection connect_on_data_received(std::function<void(const char * data, size_t size,std::string client_id)> func)= 0;
   virtual ~IAsyncServer() {}

};

}//TCP
}//NET

#endif // IASYNCSERVER_H
