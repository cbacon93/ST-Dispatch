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
   
    data.throt_r_c = db->iThrott_r.get();
    data.throt_l_c = db->iThrott_l.get();
    data.ze_c = db->iRuddr.get();
    data.et_c = db->iElev.get();
    data.xi_c = db->iAiln.get();
    data.gear_c = db->gear_lever.get();
    data.flaps_c = db->iFlaps.get();
    data.speedBrake_c = db->iSpeedBrake.get();
    data.brake_c = db->iBrake.get();
    data.wind_x = db->xWind.get();
    data.wind_y = db->yWind.get();
    data.wind_z = db->zWind.get();
    data.wind_rot_x = db->xRotWind.get();
    data.wind_rot_y = db->yRotWind.get();
    data.wind_rot_z = db->zRotWind.get();
    data.elevation = db->elevation.get();
    
    data.ap_speed_set = db->apSpeed.get();
    data.ap_alt_set = db->apAlt.get();
    data.ap_hdg_set = db->apHding.get();
    data.ap_button = db->apEngagedButton.get();
    data.ap_speed_button = db->apSpeedHoldEngagedButton.get();
    data.ap_hdg_button = db->apHDGHoldEngagedButton.get();
    data.ap_alt_button = db->apALTHoldEngagedButton.get();
    
    data.run = db->sim_running.get();
    data.reset = db->sim_resetted.get();
    
    net.sendData(&data, sizeof(data));
}


void ClientModell::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data)) {
        std::cout << "Modell Data Mismatch..." << std::endl;
        return;
    }
    
    //echo /debug/
    std::cout << "Modell Received " << n << " / " << n << " bytes" << std::endl;
    
    //save data in database
    db->vKIAS.set(data.airspeed);
    db->vKTAS.set(data.trueairspeed);
    db->vMach.set(data.mach);
    db->vKTGS.set(data.gs);
    db->vVS.set(data.vspeed);
    db->aPA.set(data.alt);
    db->aIA.set(data.alt);
    db->aHGT.set(data.alt - db->elevation.get());
    db->lat.set(data.lat);
    db->lon.set(data.lon);
    db->aRoll.set(data.roll);
    db->aPitch.set(data.pitch);
    db->aTHDG.set(data.hdg);
    db->aMHDG.set(data.hdg-0.0175);
    db->aTCRS.set(data.track);
    db->gear_pos.set(data.gear_pos);
    
    db->ilsAlive.set(data.ilsAlive);
    db->ilsLoc.set(data.ilsloc_dev);
    db->ilsGs.set(data.ilsgs_dev);
    db->apEngaged.set(data.apEngaged);
    db->apSpeedHoldEngaged.set(data.apSpeedEngaged);
    db->apHDGHoldEngaged.set(data.apHdgEngaged);
    db->apALTHoldEngaged.set(data.apAltEngaged);
}