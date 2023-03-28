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

//Large Prime
//0FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AAAC42DAD33170D04507A33A85521ABDF1CBA64ECFB850458DBEF0A8AEA71575D060C7DB3970F85A6E1E4C7ABF5AE8CDB0933D71E8C94E04A25619DCEE3D2261AD2EE6BF12FFA06D98A0864D87602733EC86A64521F2B18177B200CBBE117577A615D6C770988C0BAD946E208E24FA074E5AB3143DB5BFCE0FD108E4B82D120A92108011A723C12A787E6D788719A10BDBA5B2699C327186AF4E23C1A946834B6150BDA2583E9CA2AD44CE8DBBBC2DB04DE8EF92E8EFC141FBECAA6287C59474E6BC05D99B2964FA090C3A2233BA186515BE7ED1F612970CEE2D7AFB81BDD762170481CD0069127D5B05AA993B4EA988D8FDDC186FFB7DC90A6C08F4DF435C934063199FFFFFFFFFFFFFFFF

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
                if(key == "NODE_NAME"){
                    config["NODE_NAME"] = value;
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
