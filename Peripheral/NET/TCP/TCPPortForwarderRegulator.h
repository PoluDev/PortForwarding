#ifndef _TCP_PORT_FORWARDER_REGULATOR_H_
#define _TCP_PORT_FORWARDER_REGULATOR_H_

#include <map>
#include <memory>
#include <string>

#include "AppDef.h"
#include "DefaultLogger.h"
#include "tcpserver.h"
#include "tcpclient.h"

namespace NET{
namespace TCP{
class TCPPortForwarderRegulator
{
public:
    TCPPortForwarderRegulator(ApplicationParameter parameters, std::shared_ptr<DefaultLogger> logger);
    bool init();
    bool start();
private:
    void data_received(std::string id, const char* data, size_t size);
    void client_connected(std::string ip, std::string port, std::string client_id);
    void server_data_received(const char * data, size_t size, std::string client_id);
void client_data_received(std::string id, const char *data, size_t size);
    ApplicationParameter parameters_;
    std::shared_ptr<TCPServer> tcp_server_;
    std::shared_ptr<DefaultLogger> logger_;
    std::map<std::string, std::shared_ptr<TCPClient>> clients_list_;
};


}//TCP
}//NET

#endif // _TCP_PORT_FORWARDER_REGULATOR_H_
