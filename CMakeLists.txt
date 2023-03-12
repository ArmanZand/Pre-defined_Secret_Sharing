cmake_minimum_required(VERSION 3.24)
project(clean_sockets)

set(CMAKE_CXX_STANDARD 11)

add_executable(clean_sockets main.cpp networking/listener.cpp networking/socketHandle.h networking/socketHandle.cpp networking/socketEvents.h networking/socketEvents.cpp)

target_link_libraries(clean_sockets Ws2_32)