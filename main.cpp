#include <iostream>
#include <string>
#include <vector>

#include "AppDef.h"
#include "DefaultLogger.h"
#include "TCPPortForwarderRegulator.h"

using namespace std;

std::shared_ptr<DefaultLogger> logger_;

inline ApplicationParameter parse_parameters(int argc, char *argv[])
{
    ApplicationParameter parameter;
    parameter.dest_ = "176.31.162.201";
    parameter.bind_port_ = 1126;
    parameter.dest_port_ = 1026;
    int index = 0;
    while (index < argc)
    {
        std::string value=argv[index];
        if (index == 0)
        {
            parameter.application_path_ = value;
            logger_->log("Application Path:" + parameter.application_path_);
        }
        if (value.compare("-bind-port") == 0)
        {
            index++;
            parameter.bind_port_ = std::atoi(argv[index]);
            logger_->log("Bind Port:" + std::to_string(parameter.bind_port_));
        }
        if (value.compare("-dest-ip") == 0)
        {
            index++;
            parameter.dest_ = argv[index] ;
            logger_->log("Dest IP:" +  parameter.dest_);
        }
        if (value.compare("-dest-port") == 0)
        {
            index++;
            parameter.dest_port_ = std::atoi(argv[index]);
            logger_->log("Dest Port:" + std::to_string(parameter.dest_port_));
        }
        index++;
    }

    return parameter;
}

ApplicationParameter params;
int main(int argc, char *argv[])
{
    logger_ = std::make_shared<DefaultLogger>("port_forw.log");
    params = parse_parameters(argc, argv);
    logger_->log("Starting Regulator");
    std::shared_ptr<NET::TCP::TCPPortForwarderRegulator> regulator =
        std::make_shared<NET::TCP::TCPPortForwarderRegulator>(params, logger_);
    regulator->init();
    regulator->start();


    while(true)
    {
        //printf("%s\r\n", "Hello World!");;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}
