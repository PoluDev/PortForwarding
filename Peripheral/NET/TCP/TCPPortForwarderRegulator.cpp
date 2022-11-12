#include "TCPPortForwarderRegulator.h"


NET::TCP::TCPPortForwarderRegulator::TCPPortForwarderRegulator(ApplicationParameter parameters, std::shared_ptr<DefaultLogger> logger)
    :parameters_(parameters), logger_(logger)
{

}

void NET::TCP::TCPPortForwarderRegulator::client_connected(std::string ip, std::string port, std::string client_id)
{
    logger_->log("new client connected : " + ip +":"+port);
    std::shared_ptr<TCPClient> tcp_client = std::make_shared<TCPClient>(client_id);
    tcp_client->init();
    tcp_client->connect_on_data_received(std::bind(&TCPPortForwarderRegulator::client_data_received, this, std::placeholders::_1,
                                                   std::placeholders::_2, std::placeholders::_3));



    tcp_client->connect(parameters_.dest_, std::to_string(parameters_.dest_port_));

    clients_list_.emplace(std::make_pair(client_id, tcp_client));

}

void NET::TCP::TCPPortForwarderRegulator::client_data_received(std::string id,const  char *data, size_t size)
{
    tcp_server_->send(data, size, id);
}

void NET::TCP::TCPPortForwarderRegulator::server_data_received(const char *data, size_t size, std::string client_id)
{
    std::map<std::string, std::shared_ptr<TCPClient>>::iterator it = clients_list_.find(client_id);
    if (it != clients_list_.end())
    {
        it->second->send(data, size);
    }
    else
    {
        logger_->log("Cannot send server's data to specfici client("+client_id+")");
    }
}

bool NET::TCP::TCPPortForwarderRegulator::init()
{
    logger_->log("Start Server Module");
    tcp_server_ = std::make_shared<TCPServer>(parameters_.bind_port_);
    tcp_server_->connect_on_data_received(std::bind(&TCPPortForwarderRegulator::server_data_received, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    tcp_server_->connect_on_client_connected(std::bind(&TCPPortForwarderRegulator::client_connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    tcp_server_->init();

}

bool NET::TCP::TCPPortForwarderRegulator::start()
{
    return tcp_server_->start();
}
