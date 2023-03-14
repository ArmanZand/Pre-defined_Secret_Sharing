//
// Created by arman on 13/03/2023.
//

#ifndef CLEAN_SOCKETS_PARAMETERS_H
#define CLEAN_SOCKETS_PARAMETERS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <variant>
//TODO:
//1. correct destruction
//2. config file
//3. listener status events
//4. protobuf
//5. scripting


const int p_constBufferSize = 8192;

using namespace std;

static unordered_map<string, variant<int, bool, string>> config = {
        {"KEEP_TRYING",true},
        {"WAIT_RETRY", 1000},
        {"PREFIX_SIZE", (int)sizeof(int)}
};

class parameters {
    static void loadConfig(string filePath) {
        try {
            ifstream config_file(filePath);
            string line;
            while(getline(config_file, line)){
                istringstream iss(line);
                string key, value;
                if(getline(iss, key, '=')) {
                    if(key == "KEEP_TRYING"){
                        config["KEEP_TRYING"] = (value == "TRUE");
                        continue;
                    }
                    if(key == "WAIT_RETRY"){
                        config["WAIT_RETRY"] = stoi(value);
                        continue;
                    }
                    if(key == "PREFIX_SIZE"){
                        config["PREFIX_SIZE"] = stoi(value);
                        continue;
                    }
                    if(key == "AUTO_CONNECT") {
                        config["AUTO_CONNECT"] = value;
                        continue;
                    }
                    if(key == "LISTEN_START"){
                        config["LISTENER_START"] = value;
                        continue;
                    }
                }
            }
        } catch(exception & ex){
            cerr << ex.what() << endl;
        }
    }
};

#endif //CLEAN_SOCKETS_PARAMETERS_H
