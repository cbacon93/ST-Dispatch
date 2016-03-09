//
//  client.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client.hpp"


Client::Client(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    net(Networking())
{
    db = _db;
    net.initSocket(ip_adress, sendPort, recvPort);
    
    //start receive thread
    receiving = true;
    th = std::thread(recvThreadLoop, this);
}



void Client::recvThreadLoop(Client * inst) {
    bool running = true;
    
    do {
        //receive next information
        inst->receiveInfo();
        
        //exit if running is false
        inst->mtx.lock();
        running = inst->receiving;
        inst->mtx.unlock();
    } while(running);
}


void Client::joinThread() {
    //stop receiving
    mtx.lock();
    receiving = false;
    mtx.unlock();
    
    //join thread
    th.join();
}


Client::~Client() {
    net.closeSocket();
    joinThread();
}