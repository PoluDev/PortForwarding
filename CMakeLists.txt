cmake_minimum_required(VERSION 3.5)

project(CPPPortForwarder LANGUAGES CXX)


find_package(Boost COMPONENTS system filesystem iostreams thread REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CPPPortForwarder main.cpp  AppDef.h DefaultLogger.h DefaultLogger.cpp IAsyncServer.h IAsyncClient.h  TCPPortForwarderRegulator.h TCPPortForwarderRegulator.cpp tcpserver.cpp tcpserver.h tcpclient.cpp tcpclient.h)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#./CPPPortForwarder -bind-port 1026 -dest-ip 192.168.1.21 -dest-port 1080

