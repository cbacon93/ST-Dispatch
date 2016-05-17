//
//  client_modell.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 17.05.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_modell.hpp"


void ClientModell::sendInfo() {
    sendData data;
   
    data.throt_c = db->iThrott.get();
    data.ze_c = db->iRuddr.get();
    data.et_c = db->iElev.get();
    data.xi_c = db->iAiln.get();
    data.gear_c = db->gear_lever.get();
    data.flaps_c = db->iFlaps.get();
    data.speedBrake_c = db->iSpeedBreak.get();
    data.brake_c = db->iBreak.get();
    data.wind_x = db->xWind.get();
    data.wind_y = db->yWind.get();
    data.wind_z = db->zWind.get();
    data.wind_rot_x = db->xRotWind.get();
    data.wind_rot_y = db->yRotWind.get();
    data.wind_rot_z = db->zRotWind.get();
    data.elevation = db->elevation.get();
    
    data.run = db->sim_running.get();
    data.reset = db->sim_resetted.get();
    
    net.sendData(&data, sizeof(data));
}


void ClientModell::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data)) {
        std::cout << "Data Mismatch..." << std::endl;
        return;
    }
    
    //echo /debug/
    std::cout << "Modell Received " << n << " / " << n << " bytes" << std::endl;
    
    //save data in database
    db->vKIAS.set(data.airspeed);
    db->vKTAS.set(data.airspeed);
    db->vMach.set(data.airspeed/data.soundspeed);
    db->vVS.set(data.vspeed);
    db->aPA.set(data.alt);
    db->aIA.set(data.alt);
    db->lat.set(data.lat);
    db->lon.set(data.lon);
    db->aRoll.set(data.roll);
    db->aPitch.set(data.pitch);
    db->aTHDG.set(data.hdg);
    db->aMHDG.set(data.hdg-0.05);
    db->aTCRS.set(data.track);
    db->gear_up.set(data.gear_up);
    db->gear_down.set(data.gear_dn);
}