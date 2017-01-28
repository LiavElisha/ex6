cmake_minimum_required(VERSION 3.6)
project(ex6)

###############################
#set(g++ -std=c++0x main.cpp BFS.cpp -lboost_serialization -o client)
###############################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
###############################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
###############################

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system log)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

ADD_DEFINITIONS(-DBOOST_LOGDYN_LINK)

set(SOURCE_FILES src/main.cpp src/Point.cpp src/Point.h  src/AbstractNode.cpp
        src/AbstractNode.h src/NodePoint.cpp
        src/NodePoint.h src/Grid.cpp src/Grid.h src/Matrix.cpp src/Matrix.h
        src/Bfs.cpp src/Bfs.h  src/Bfs.h
        src/AbstractCab.cpp src/AbstractCab.h src/StandardCab.cpp src/StandardCab.h src/LuxuryCab.cpp src/LuxuryCab.h
        src/Passanger.cpp src/Passanger.h src/Socket.cpp src/Socket.h src/Udp.cpp src/Udp.h
        src/TaxiCenter.cpp src/TaxiCenter.h src/Driver.cpp src/Driver.h
        src/TripInformation.cpp src/TripInformation.h
        src/TripInformation.h
        src/Menu.cpp src/Menu.h src/Data.cpp  src/Data.h src/Tcp.cpp src/Tcp.h
        src/Communication.cpp src/Communication.h src/InputValidator.cpp src/InputValidator.h
        src/Job.cpp src/Job.h src/ThreadPool.cpp src/ThreadPool.h)

#add_executable(ex6 ${SOURCE_FILES})
add_executable(server src/Server.cpp ${SOURCE_FILES})
add_executable(client src/Client.cpp ${SOURCE_FILES} src/Tcp.cpp src/Tcp.h src/Data.cpp src/Data.h src/Communication.cpp src/Communication.h src/Job.cpp src/Job.h src/ThreadPool.cpp src/ThreadPool.h)


target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
#target_link_libraries(ex6 gtest gtest_main)
