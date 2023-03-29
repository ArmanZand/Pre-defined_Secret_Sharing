//
// Created by arman on 14/03/2023.
//
#include <functional>
#include "resolver.h"
#include "consoleLog.h"
using commandHandler = function<void(socketHandle *, protobufMessage &)>;
unordered_map<protobufMessage::CommandCase, commandHandler> commands = {
        { protobufMessage::kNodeInfo, resolver::nodeInfo },
        { protobufMessage::kNodeInfoReply, resolver::nodeInfoReply },
        { protobufMessage::kNodeInfoAck, resolver::nodeInfoAck },
        { protobufMessage::kNodePayload, resolver::nodePayload },
        { protobufMessage::kDealerShare, resolver::dealerShare },
        { protobufMessage::kBroadcastShare, resolver::broadcastShare }
};
void resolver::execute(socketHandle *handlePtr, protobufMessage &pm) {
    try {
        auto it = commands.find(pm.command_case());
        if(it != commands.end()){
            it->second(handlePtr, pm);
        }
        else {
            throw runtime_error("Command not recognised.");
        }

    }
    catch(exception & ex){
        consoleLog::print(ex.what(), LogLevel::ERR);
    }
}
void resolver::nodeInfo(socketHandle *handlePtr, protobufMessage &pm){
    handlePtr->name = pm.nodeinfo().name();
    handlePtr->id = bignum::parseStr(pm.nodeinfo().id().c_str());
    handlePtr->type = pm.nodeinfo().type();
    string print_str = "NODE INFO RECEIVED (" + handlePtr->ip + "):\n\t- NAME: " + handlePtr->name + "\n\t- ID: " + handlePtr->id.toStr() + "\n\t- TYPE: " + nodeTypeNames[handlePtr->type];
    consoleLog::print(print_str);
//    cout << "Discovered Node Info for " << handlePtr->ip << ":" << endl;
//    cout << "\tName: " << handlePtr->name << endl;
//    cout << "\tId: " << handlePtr->id.toStr() << endl;
//    cout << "\tType: " << nodeTypeNames[handlePtr->type] << endl;
    protobufMessage rm;
    rm.mutable_nodeinforeply()->set_id(get<bignum>(config["NODE_ID"]).toStr());
    rm.mutable_nodeinforeply()->set_name(get<string>(config["NODE_NAME"]));
    rm.mutable_nodeinforeply()->set_type(static_cast<nodeType>(get<int>(config["NODE_TYPE"])));
    handlePtr->send(rm);
}

void resolver::nodeInfoReply(socketHandle *handlePtr, protobufMessage &pm){
    handlePtr->name = pm.nodeinforeply().name();
    handlePtr->id = bignum::parseStr(pm.nodeinforeply().id().c_str());
    handlePtr->type = pm.nodeinforeply().type();
    string print_str = "NODE INFO RECEIVED (" + handlePtr->ip + "):\n\t- NAME: " + handlePtr->name + "\n\t- ID: " + handlePtr->id.toStr() + "\n\t- TYPE: " + nodeTypeNames[handlePtr->type];
    consoleLog::print(print_str);
//    cout << "Discovered Node Info for " << handlePtr->ip << ":" << endl;
//    cout << "\tName: " << handlePtr->name << endl;
//    cout << "\tId: " << handlePtr->id.toStr() << endl;
//    cout << "\tType: " << nodeTypeNames[handlePtr->type] << endl;
    protobufMessage rm;
    rm.mutable_nodeinfoack();
    handlePtr->send(rm);

    secretSharerProcedure(handlePtr);
    dealerProcedure();
}

void resolver::nodeInfoAck(socketHandle *handlePtr, protobufMessage &pm){
    secretSharerProcedure(handlePtr);
    dealerProcedure();
}

void resolver::nodePayload(socketHandle *handlePtr, protobufMessage &pm) {
    bignum payloadValue = bignum::parseStr(pm.nodepayload().payload().c_str());
    string print_str = "RECEIVED PAYLOAD FROM " + handlePtr->name+ " (" + handlePtr->ip + "):\n\t- CONTENT:\n" + payloadValue.toStr();
    consoleLog::print(print_str);
//    cout << "Received payload from " <<  nodeTypeNames[handlePtr->type] << " (" << handlePtr->ip << ")." << endl;
//    cout << "Payload content: " << endl;

//    cout << payloadValue.toStr() << endl;
    playerSecrets.push_back(payloadValue);
    dealerProcedure();
}
vector<point> resolver::receivedShares;
void resolver::dealerShare(socketHandle *handlePtr, protobufMessage &pm) {
    bignum share_x = bignum::parseStr(pm.dealershare().x().c_str());
    bignum share_y = bignum::parseStr(pm.dealershare().y().c_str());
    string print_str = "RECEIVED `DEALER' SHARE FROM " + handlePtr->name+ " (" + handlePtr->ip + "):\n\t- X:\n" + share_x.toStr() + "\n\t- Y:\n" + share_y.toStr();
    consoleLog::print(print_str);
//    cout << "Received share from "<<  nodeTypeNames[handlePtr->type] << " (" << handlePtr->ip << ")." << endl;
//    cout << "Share content: " << endl;
//
//    cout << "X: " << share_x.toStr() << endl;
//    cout << "Y: " << share_y.toStr() << endl;
    receivedShares.push_back(point(share_x, share_y));

    protobufMessage rm;
    rm.mutable_broadcastshare()->set_x(pm.dealershare().x());
    rm.mutable_broadcastshare()->set_y(pm.dealershare().y());
    for(socketHandle * handlePtr : handleTracker::m_handles){
        if(handlePtr->type == nodeType::secretRecoverer){
            handlePtr->send(rm);
        }
    }
}

void resolver::secretSharerProcedure(socketHandle *handlePtr) {
    if(get<int>(config["NODE_TYPE"]) != nodeType::secretSharer) return;
    if(handlePtr->type == nodeType::dealer){
        consoleLog::print("Secret Sharer procedure Activated.");
        //cout << "Starting " << nodeTypeNames[get<int>(config["NODE_TYPE"])] << " procedure for " << nodeTypeNames[nodeType::dealer] <<"..." << endl;
        if(parameters::keyExists("PLAYER_SECRET")){
            bignum player_secret = get<bignum>(config["PLAYER_SECRET"]);
            protobufMessage rm;
            rm.mutable_nodepayload()->set_payload(player_secret.toStr());
            handlePtr->send(rm);
            consoleLog::print("Sent payload to " + handlePtr->name +" ("  + handlePtr->ip  + ").");
            //cout << "Sent payload to " << nodeTypeNames[nodeType::dealer] << "." << endl;
        }else {
            consoleLog::print("Did not detect a player secret, procedure end.", LogLevel::WARNING);
            //cout << "Did not detect a player secret, procedure end." << endl;
        }
    }
}

vector<bignum> resolver::playerSecrets;

void resolver::dealerProcedure() {
    if(get<int>(config["NODE_TYPE"]) != nodeType::dealer && !parameters::keyExists("NUM_PRE_DEFINED_SHARES") && !parameters::keyExists("DEALER_SECRET")) return;
    int num_predef_shares = get<int>(config["NUM_PRE_DEFINED_SHARES"]);
    vector<socketHandle *> secretRecoverers;
    for(socketHandle * handlePtr : handleTracker::m_handles){
        if(handlePtr->type == nodeType::secretRecoverer){
            secretRecoverers.push_back(handlePtr);
        }
    }
    //
    if(playerSecrets.size() == num_predef_shares && secretRecoverers.size() > 0) {
        consoleLog::print(to_string(num_predef_shares) + " pre-defined shares have been received.");
        //cout << num_predef_shares << "pre-defined shares have been received." << endl;
        vector<point> predef_shares;
        bignum null = bignum(0);
        bignum dealerSecret = get<bignum>(config["DEALER_SECRET"]);
        point dealerPoint = point(null, dealerSecret);
        predef_shares.push_back(dealerPoint);

        bignum x_value_min = bignum(1);
        bignum bignum_one = bignum("1");
        bignum x_value_max = get<bignum>(config["PRIME"]) - bignum_one;
        vector<bignum> distinctBignums = cryptoUtilities::uniqueBignumVector(num_predef_shares + secretRecoverers.size(), x_value_min, x_value_max);
        for(int i = 0; i < num_predef_shares; i++){
            bignum x_val = distinctBignums[i];
            bignum y_val = playerSecrets[i];
            cout << "Secret Index: " << x_val.toStr() << endl;
            predef_shares.push_back(point(x_val, y_val));
        }
        bignum prime = get<bignum>(config["PRIME"]);
        polynomial p(&prime);
        p.interpolate(predef_shares);
        for(int i = 0; i < secretRecoverers.size(); i++){
            protobufMessage rm;
            bignum eval_x = distinctBignums[num_predef_shares+i];
            rm.mutable_dealershare()->set_x(eval_x.toStr());
            rm.mutable_dealershare()->set_y(p.evaluate(eval_x).y.toStr());
            secretRecoverers[i]->send(rm);
            consoleLog::print("SENT SHARE TO " + secretRecoverers[i]->name + " (" + secretRecoverers[i]->ip + ").");
            //cout << "Sent share to "<< secretRecoverers[i]->name << endl;
        }
        playerSecrets.clear();
    }
}

void resolver::secretRecovererProcedure() {
    if(get<int>(config["NODE_TYPE"]) != nodeType::secretRecoverer && !parameters::keyExists("THRESHOLD")) return;
    int threshold = get<int>(config["THRESHOLD"]);
    if(receivedShares.size() != threshold) return;
    bignum prime = get<bignum>(config["PRIME"]);
    polynomial p(&prime);
    p.interpolate(receivedShares);
    consoleLog::print("Recovered a polynomial, enter a pre-defined share `x' value:");
    string input;
    bool stopped = false;
    while(!stopped){
        cout << "Input > ";
        std::getline(std::cin, input);
        if(input == "stop"){
            stopped = true;
        } else {
            try {
                bignum parse_x = bignum::parseStr(input.c_str());
                string result = p.evaluate(parse_x).y.toStr();
                consoleLog::print("Result: " + result);
            }
            catch(exception & ex){
                consoleLog::print(ex.what(), LogLevel::ERR);
            }
        }
    }

}

void resolver::broadcastShare(socketHandle *handlePtr, protobufMessage &pm) {
    bignum share_x = bignum::parseStr(pm.broadcastshare().x().c_str());
    bignum share_y = bignum::parseStr(pm.broadcastshare().y().c_str());
    string print_str = "RECEIVED `BROADCASTED' SHARE FROM " + handlePtr->name+ " (" + handlePtr->ip + "):\n\t- X:\n" + share_x.toStr() + "\n\t- Y:\n" + share_y.toStr();
    consoleLog::print(print_str);
//    cout << "Received broadcasted share from "<<  nodeTypeNames[handlePtr->type] << " (" << handlePtr->ip << ")." << endl;
//    cout << "Share content: " << endl;
//
//    cout << "X: " << share_x.toStr() << endl;
//    cout << "Y: " << share_y.toStr() << endl;
    receivedShares.push_back(point(share_x, share_y));
    secretRecovererProcedure();
}

//void resolver::exampleMessage(socketHandle &handle, protobufMessage &pm) {
//    cout << handle.ip << "> " << pm.examplemessage().message() << endl;
//}
