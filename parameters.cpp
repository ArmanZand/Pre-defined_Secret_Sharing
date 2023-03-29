//
// Created by arman on 29/03/2023.
//
#include "parameters.h"

const char * nodeTypeNames[] = { "undefined", "secret sharer", "dealer", "secret recover"};
unordered_map<string, variant<int, bool, string, bignum>> config = {
    {"KEEP_TRYING",true},
    {"WAIT_RETRY", 1000},
    { "NODE_ID", bignum("0")},
    { "NODE_NAME", string("Node")},
    { "NODE_TYPE", 0}
};

bool parameters::keyExists(string key) {
    return config.count(key) > 0;
}

variant<int, bool, string, bignum> parameters::find(string key) {
    auto it = config.find(key);
    if(it != config.end()){
        return it->second;
    }else {
        throw runtime_error("Key not found.");
    }
}

void parameters::loadConfig(string filePath){
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
            if(key == "GENERATE_RANDOM_ID"){
                config["GENERATE_RANDOM_ID"] = (value == "TRUE");
                if(value == "TRUE"){
                    config["NODE_ID"] = cryptoUtilities::nextBignum(1,999);
                }
                continue;
            }
            if(key == "NODE_ID"){
                config["NODE_ID"] = bignum::parseStr(value.c_str());
                continue;
            }
            if(key == "NODE_NAME"){
                config["NODE_NAME"] = value;
                continue;
            }
            if(key == "NODE_TYPE"){
                config["NODE_TYPE"] = stoi(value);
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