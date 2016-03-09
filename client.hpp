//
//  client.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_hpp
#define client_hpp

#include <string>
#include <thread>
#include <mutex>
#include "networking.hpp"
#include "database.hpp"

/*
 Templateklasse für den Clienten
 Wird später an Unterklassen vererbt
 
 Empfängt Daten, speichert sie in der Database und
 sendet sie per Call von der main.cpp an den Clienten.
 
 Jeder Client besitzt seine eigene Instanz
 */

class Client {
private:
    Networking net;
    std::thread th;
    Database *db;
public:
    Client(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort);
    ~Client();
    void joinThread();
    static void recvThreadLoop(Client * inst);
    
    //sending and receiving data
    virtual void sendInfo() {}
    virtual void receiveInfo() {}
    
    bool receiving;
    std::mutex mtx;
};

#endif /* client_hpp */
