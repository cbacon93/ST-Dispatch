//
//  client_anzeigen.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.04.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_environment.hpp"


void ClientEnvironment::sendInfo() {
    sendData data;
    
    //take data from database
    data.x = db->lat.get();
    data.y = db->lon.get();
    data.z = db->aHGT.get();
    data.phi = db->aRoll.get();
    data.theta = db->aPitch.get();
    data.psi = db->aTHDG.get();
    
    net.sendData(&data, sizeof(data));
    
}

void ClientEnvironment::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data))
        return;
    
    //echo /debug/
    std::cout << "Received " << n << " bytes - counter: " << data.counter << " / " << n << std::endl;
    
    //save data in database
    db->xWind.set(data.u);
    db->yWind.set(data.v);
    db->zWind.set(data.w);
    db->iElev.set(data.Elevation);
    
}