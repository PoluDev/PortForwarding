#ifndef __I_ASYNC_CLIENT_H__
#define __I_ASYNC_CLIENT_H__

#include <functional>
#include <iostream>
#include <mutex>
#include <string>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

namespace NET{
namespace TCP{

class IAsyncClient{
public:
    struct LanAddress {

    public:
        LanAddress() {}
        LanAddress(const std::string ipaddress, const short port) : ipaddress_(ipaddress), port_(port)
        {

        }
        bool operator ==(const LanAddress& lanAddress)
        {
            if (lanAddress.ipaddress_ == ipaddress_ && port_ == lanAddress.port_)
                return true;
            return false;
        }

        std::string ipaddress_;
        short port_;
    };


    virtual void init() =0;
    virtual bool connect(std::string ipaddress, std::string port) =0;
    virtual bool connect(LanAddress end_point) =0;
    virtual void disconnect() =0;
    virtual void send(const char* buffer, size_t size) =0;
    virtual bool is_connected() const =0;
    virtual std::string get_id() const =0;
    virtual boost::signals2::connection connect_on_data_received(std::function<void(std::string id, const char* data, size_t size)> func)=0;

    virtual ~IAsyncClient(){}

};
}
}

#endif // __I_ASYNC_CLIENT_H__
