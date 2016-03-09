//
//  client_example.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 09.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_example.hpp"


void ClientExample::sendInfo() {
    sendData data;
    
    //take data from database
    data.counter = db->exampleCounter.get() + 1;
    data.reset = db->sim_resetted.get();
    data.running = db->sim_running.get();
    
    net.sendData(&data, sizeof(data));
}


void ClientExample::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data))
        return;
    
    //echo /debug/
    std::cout << "Received " << n << " bytes - counter: " << data.counter << " / " << n << std::endl;
    
    //save data in database
    db->exampleCounter.set(data.counter);
}