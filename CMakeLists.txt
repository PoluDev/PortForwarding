cmake_minimum_required(VERSION 3.5)
#https://github.com/Kitware/CMake/blob/master/Modules/FindBoost.cmake
project(CPPPortForwarder VERSION 1.0)

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

if(${MSVC_VERSION})
        set(BOOST_ROOT C:/boost/boost_1_80_0/boost_1_80_0)
        set(Boost_NO_SYSTEM_PATHS ON)
        set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
        set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
        set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
        set(Boost_USE_MULTITHREADED      ON)
        set(Boost_USE_STATIC_RUNTIME    OFF)
        set(Boost_NO_WARN_NEW_VERSIONS 1)
        #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
       # set(CMAKE_CXX_FLAGS_RELEASE "/MT")
        set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
        add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif(${MSVC_VERSION})
#find_package(Threads)
find_package(Boost REQUIRED COMPONENTS date_time thread filesystem system)


message(${Boost_VERSION})
message(${Boost_INCLUDE_DIRS})



set(HEADER_FILE_LIST
    "AppDef.h"
    "DataAccess/Log/DefaultLogger.h"
    "Peripheral/NET/TCP/IAsyncClient.h"
    "Peripheral/NET/TCP/IAsyncServer.h"
    "Peripheral/NET/TCP/tcpclient.h"
    "Peripheral/NET/TCP/TCPPortForwarderRegulator.h"
    "Peripheral/NET/TCP/tcpserver.h"
    )

set(SOURCE_FILE_LIST
    "main.cpp"
    "DataAccess/Log/DefaultLogger.cpp"
    "Peripheral/NET/TCP/tcpclient.cpp"
    "Peripheral/NET/TCP/TCPPortForwarderRegulator.cpp"
    "Peripheral/NET/TCP/tcpserver.cpp"
    )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(CPPPortForwarder ${HEADER_FILE_LIST} ${SOURCE_FILE_LIST})
#target_include_directories(${PROJECT_NAME}  PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} Boost::filesystem Boost::)

#./CPPPortForwarder -bind-port 1026 -dest-ip 192.168.1.21 -dest-port 1080

