//
// Created by arman on 29/03/2023.
//

#include "consoleLog.h"
std::mutex console_mutex;
void consoleLog::print(const std::string &message, const LogLevel level) {

    std::lock_guard<std::mutex> lock(console_mutex);
    switch(level){
        case LogLevel::DEBUG:
            std::cout << "[DEBUG] ";
            break;
        case LogLevel::WARNING:
            std::cout << "[WARNING] ";
            break;
        case LogLevel::ERR:
            std::cerr << "[ERROR] ";
            break;
    }
    std::cout << message << std::endl;
}