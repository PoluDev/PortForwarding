#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include "IAsyncServer.h"

namespace NET{
namespace TCP{

class TCPServer : public IAsyncServer
{

public:
    struct TCPClientEntity
    {
    public:
        TCPClientEntity(std::string id, std::shared_ptr<boost::asio::ip::tcp::socket> client, std::array<char, 22808> array)
        {
            id_ = id;
            client_ = client;
            receiveBuffer_ =array;
        }
        std::string id_;
        std::array<char, 22808> receiveBuffer_;
        std::shared_ptr<boost::asio::ip::tcp::socket> get_socket()
        {
            return client_;
        }
    private:
        std::shared_ptr<boost::asio::ip::tcp::socket> client_;
    };

public:
    TCPServer(unsigned short bind_port);

    // IAsyncServer interface
public:
    void init();
    bool start();
    bool stop();
    bool is_running() const;
    void send(const char *data, size_t size, std::string client_id);
    boost::signals2::connection connect_on_client_connected(std::function<void (std::string, std::string, std::string)> func);
    boost::signals2::connection connect_on_data_received(std::function<void (const char *, size_t, std::string)> func);

private:
    unsigned short bind_port_;
    bool is_running_;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    std::shared_ptr<boost::asio::ip::tcp::socket> client_;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::shared_ptr<boost::asio::io_service> ioService_;
    boost::asio::ip::tcp::endpoint serverEndPoint_;
    boost::thread_group threadGroup_;
    std::array<char, 22808> receiveBuffer_;
    std::mutex mtx;
    std::mutex mtx_r;
    std::mutex mtx_accept;
    std::mutex mtx_id;
    std::map<std::string, std::shared_ptr<TCPClientEntity>> connection_map_;

    boost::signals2::signal<void(std::string ip, std::string port, std::string client_id)> new_client_connection_;
    boost::signals2::signal<void(const char * data, size_t size,std::string client_id)> data_received_connections_;

    boost::asio::ip::tcp::endpoint getEndPoint(std::string ipaddress, std::string port_number);
    void handle_read(const boost::system::error_code & erro, size_t bytes_transferred, std::shared_ptr<TCPClientEntity> client, std::string clientid);
    void handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> client, const boost::system::error_code & error);
    void workerThread(std::shared_ptr<boost::asio::io_service> ioService);
    std::string get_new_client_id();
};

}
}

#endif // TCPSERVER_H
