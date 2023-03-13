cmake_minimum_required(VERSION 3.24)
project(clean_sockets)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "C://vcpkg//packages//protobuf_x64-windows//share//protobuf")
find_package(Protobuf CONFIG REQUIRED)

add_executable(clean_sockets main.cpp networking/listener.cpp networking/socketHandle.h networking/socketHandle.cpp networking/socketEvents.h networking/socketEvents.cpp networking/parameters.h networking/networkMessage.pb.h networking/networkMessage.pb.cc)

include_directories("C://vcpkg//packages//protobuf_x64-windows//include")
target_link_libraries(clean_sockets
        PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        Ws2_32
        )