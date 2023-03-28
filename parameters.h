//
// Created by arman on 13/03/2023.
//

#ifndef CLEAN_SOCKETS_PARAMETERS_H
#define CLEAN_SOCKETS_PARAMETERS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <variant>
#include "bignum.h"
//TODO:
//- listener stop
//- listener status events


const int p_constBufferSize = 8192;
const int p_constPrefixSize = sizeof(int);
using namespace std;

static unordered_map<string, variant<int, bool, string, bignum>> config = {
        {"KEEP_TRYING",true},
        {"WAIT_RETRY", 1000}
};

class parameters {
public:
    static bool keyExists(string key) {
        return config.count(key) > 0;
    }
    static variant<int, bool, string, bignum> find(string key){
        auto it = config.find(key);
        if(it != config.end()){
            return it->second;
        }else {
            throw runtime_error("Key not found.");
        }
    }
    static void loadConfig(string filePath) {
        try {
            cout << "Reading config file: " << filePath << endl;
            ifstream config_file(filePath);
            string line;
            while(getline(config_file, line)){
                istringstream iss(line);
                string key, value;
                getline(getline(iss >> ws, key, '='), value);
                if(key == "KEEP_TRYING"){
                    config["KEEP_TRYING"] = (value == "TRUE");
                    continue;
                }
                if(key == "WAIT_RETRY"){
                    config["WAIT_RETRY"] = stoi(value);
                    continue;
                }
                if(key == "AUTO_CONNECT") {
                    config["AUTO_CONNECT"] = value;
                    continue;
                }
                if(key == "LISTENER_START"){
                    config["LISTENER_START"] = value;
                    continue;
                }
                if(key == "PRIME_HEX") {
                    config["PRIME"] = bignum::parseHex(value.c_str());
                    continue;
                }
                if(key == "PRIME") {
                    config["PRIME"] = bignum::parseStr(value.c_str());
                    continue;
                }
                if(key == "PLAYER_SECRET_HEX") {
                    config["PLAYER_SECRET_HEX"] = bignum::parseHex(value.c_str());
                    continue;
                }
                if(key == "PLAYER_SECRET_BIGNUM") {
                    config["PLAYER_SECRET_BIGNUM"] = bignum::parseStr(value.c_str());
                    continue;
                }
                if(key == "DEALER_SECRET_HEX") {
                    config["DEALER_SECRET_HEX"] = bignum::parseHex(value.c_str());
                    continue;
                }
                if(key == "DEALER_SECRET_BIGNUM"){
                    config["DEALER_SECRET_BIGNUM"] = bignum::parseStr(value.c_str());
                    continue;
                }
            }
        } catch(exception & ex){
            cerr << ex.what() << endl;
        }
    }
};

#endif //CLEAN_SOCKETS_PARAMETERS_H
