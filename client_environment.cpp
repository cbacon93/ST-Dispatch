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
    data.lat = db->lat.get();
    data.lon = db->lon.get();
    data.talt = db->aPA.get();
    data.phi = db->aRoll.get();
    data.theta = db->aPitch.get();
    data.psi = db->aTHDG.get();
    
    net.sendData(&data, sizeof(data));
    
}

void ClientEnvironment::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abor
    if (n != sizeof(data))
        return;
    
    //echo /debug/
    std::cout << "Environment Received " << n << " / " << n << " bytes" << std::endl;
    
    //save data in database
    db->xWind.set(data.xwind);
    db->yWind.set(data.ywind);
    db->zWind.set(data.zwind);
    db->elevation.set(data.elevation);
    db->dirWind.set(data.winddir);
    db->vWind.set(data.windspeed);
}