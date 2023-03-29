//
// Created by arman on 29/03/2023.
//

#ifndef CLEAN_SOCKETS_CONSOLELOG_H
#define CLEAN_SOCKETS_CONSOLELOG_H
#include <iostream>
#include <string>
#include <mutex>

enum class LogLevel { INFO , DEBUG , WARNING, ERR };
class consoleLog {
public:
    static void print(const std::string &message, const LogLevel level = LogLevel::INFO);
};


#endif //CLEAN_SOCKETS_CONSOLELOG_H
