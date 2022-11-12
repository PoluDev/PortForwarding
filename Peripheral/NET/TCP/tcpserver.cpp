#include "tcpserver.h"


NET::TCP::TCPServer::TCPServer(unsigned short bind_port):bind_port_(bind_port)
{

}

uint32_t rand32()
{
    return ((rand() & 0x3) << 30) | ((rand() & 0x7fff) << 15) | (rand() & 0x7fff);
}

bool gen_uuid4(char dst[37], size_t len)
{
    int n = snprintf(dst, len, "%08x-%04x-%04x-%04x-%04x%08x",
                     rand32(),                         // Generates a 32-bit Hex number
                     rand32() & 0xffff,                // Generates a 16-bit Hex number
                     ((rand32() & 0x0fff) | 0x4000),   // Generates a 16-bit Hex number of the form 4xxx (4 indicates the UUID version)
                     (rand32() & 0x3fff) + 0x8000,     // Generates a 16-bit Hex number in the range [0x8000, 0xbfff]
                     rand32() & 0xffff, rand32());     // Generates a 48-bit Hex number

    return n >= 0 && n < len;             // Success only when snprintf result is a positive number and the provided buffer was large enough.
}

void NET::TCP::TCPServer::init()
{
    ioService_ = std::make_shared<boost::asio::io_service>();
    work_ = std::make_shared<boost::asio::io_service::work>(*ioService_);
}

bool NET::TCP::TCPServer::start()
{
    threadGroup_.create_thread(std::bind(&TCPServer::workerThread, this, ioService_));

    acceptor_ = std::make_shared<boost::asio::ip::tcp::acceptor>(*ioService_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), bind_port_));

    std::shared_ptr<boost::asio::ip::tcp::socket> temp = std::make_shared<boost::asio::ip::tcp::socket>(*ioService_);

    boost::system::error_code ec;
    acceptor_->listen(boost::asio::socket_base::max_connections, ec);
    if (ec)
    {
        // An error occurred.
    }

    acceptor_->async_accept(*temp, boost::bind(&TCPServer::handle_accept, this, temp, boost::asio::placeholders::error));

    is_running_ = true;
  return is_running_;

}

bool NET::TCP::TCPServer::stop()
{
    is_running_ = false;
}

bool NET::TCP::TCPServer::is_running() const
{
    return is_running_;
}

void NET::TCP::TCPServer::send(const char *data, size_t size, std::string client_id)
{
    std::map<std::string, std::shared_ptr<TCPClientEntity>>::iterator it = connection_map_.find(client_id);
    if (it != connection_map_.end())
    {
        it->second->get_socket()->send(boost::asio::buffer(data, size));
    }
}

boost::signals2::connection NET::TCP::TCPServer::connect_on_client_connected(std::function<void (std::string, std::string, std::string)> func)
{
    return new_client_connection_.connect(func);
}

boost::signals2::connection NET::TCP::TCPServer::connect_on_data_received(std::function<void (const char *, size_t, std::string)> func)
{
    return data_received_connections_.connect(func);
}

boost::asio::ip::tcp::endpoint NET::TCP::TCPServer::getEndPoint(std::string ipaddress, std::string port_number)
{
    boost::asio::ip::tcp::resolver resolver(*ioService_);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), ipaddress, port_number);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    return endpoint;
}

void NET::TCP::TCPServer::handle_read(const boost::system::error_code &erro, size_t bytes_transferred, std::shared_ptr<NET::TCP::TCPServer::TCPClientEntity> client, std::string clientid)
{
    mtx_r.lock();
    if ((boost::asio::error::eof == erro) || (boost::asio::error::connection_reset == erro))
    {
        printf("error in receiving data in tcp server so .... deleteing connection from map NetID: %s\n", clientid.c_str());
        //clientdisconnected_(client);
        connection_map_.erase(clientid);
    }
    else
    {
        if (bytes_transferred > 0)
        {
            printf("tcp server recevied some data \n");
            std::map<std::string, std::shared_ptr<TCPClientEntity>>::iterator it = connection_map_.find(clientid);
            if (it != connection_map_.end())
            {

                data_received_connections_(client->receiveBuffer_.data(), bytes_transferred, clientid);
                std::shared_ptr<boost::asio::ip::tcp::socket> socket = client->get_socket();
                socket->async_receive(boost::asio::buffer(client->receiveBuffer_.data(), client->receiveBuffer_.size()),
                                      boost::bind(&TCPServer::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, client, clientid));
            }

        }
    }

    mtx_r.unlock();
}

void NET::TCP::TCPServer::handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> client, const boost::system::error_code &error)
{ ;
   // mtx_accept.lock();
    //while (true)
    //{
        //getting remote ip address
        boost::asio::ip::tcp::endpoint remote_ep = client->remote_endpoint();
        boost::asio::ip::address remote_ad = remote_ep.address();

        std::string client_id = get_new_client_id();
        std::map<std::string, std::shared_ptr<TCPClientEntity>>::iterator it = connection_map_.find(client_id);
        if (it == connection_map_.end())
        {
            std::array<char, 22808> buffer;
            std::shared_ptr<TCPClientEntity> tcpclient = std::make_shared<TCPClientEntity>(client_id, client, buffer);
            connection_map_.emplace(std::make_pair(client_id, tcpclient));

            new_client_connection_(remote_ad.to_string(), std::to_string(remote_ep.port()), client_id);

            client->async_receive(boost::asio::buffer(tcpclient->receiveBuffer_.data(), tcpclient->receiveBuffer_.size()),
                                  boost::bind(&TCPServer::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, tcpclient, client_id));

            std::shared_ptr<boost::asio::ip::tcp::socket> temp = std::make_shared<boost::asio::ip::tcp::socket>(*ioService_);

            acceptor_->async_accept(*temp, boost::bind(&TCPServer::handle_accept, this, temp, boost::asio::placeholders::error));

       //     break;
         }
  //  }
   // mtx_accept.unlock();
}

void NET::TCP::TCPServer::workerThread(std::shared_ptr<boost::asio::io_service> ioService)
{
    try
    {
        while (is_running_)
        {
            boost::system::error_code ec;
            ioService->run(ec);
        }
    }
    catch (std::exception& ex)
    {

    }
}

std::string NET::TCP::TCPServer::get_new_client_id()
{
    char strUuid[37];
    srand(time(NULL));

    while(!gen_uuid4(strUuid, sizeof(strUuid)))
    {

    }
    std::string temp(strUuid, strUuid +37);
    return temp;
}
