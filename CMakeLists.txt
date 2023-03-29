cmake_minimum_required(VERSION 3.24)
project(clean_sockets)
set(CMAKE_CXX_STANDARD 17)

#Toolchain:
#Visual Studio 17 2022

add_executable(clean_sockets main.cpp networking/listener.cpp networking/socketHandle.h networking/socketHandle.cpp networking/socketEvents.h networking/socketEvents.cpp parameters.h networking/networkMessage.pb.cc resolver.cpp resolver.h cryptography/cryptoUtilities.cpp cryptography/cryptoUtilities.h bignum.cpp bignum.h cryptography/polynomial.cpp cryptography/polynomial.h parameters.cpp consoleLog.cpp consoleLog.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include")
target_link_libraries(clean_sockets
        "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/libprotobufd.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/gmp.lib"
        Bcrypt
        Ws2_32
        )