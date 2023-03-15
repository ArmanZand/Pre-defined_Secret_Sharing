cmake_minimum_required(VERSION 3.24)
project(clean_sockets)
set(CMAKE_CXX_STANDARD 17)

add_executable(clean_sockets main.cpp networking/listener.cpp networking/socketHandle.h networking/socketHandle.cpp networking/socketEvents.h networking/socketEvents.cpp parameters.h networking/networkMessage.pb.cc resolver.cpp resolver.h cryptography/cryptoUtilities.cpp cryptography/cryptoUtilities.h)

include_directories("C:/protobuf/include")
target_link_libraries(clean_sockets
        "C:/protobuf/lib/libprotobufd.lib"
        Bcrypt
        Ws2_32
        )