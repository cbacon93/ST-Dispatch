//
//  client_hardware.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.04.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_hardware.hpp"


void ClientHardware::sendInfo() {
    sendData data;
    
    //take data from database
    data.gear_up = db->gear_up.get();
    data.gear_down = db->gear_down.get(); //2 doubles zu bool zusammengefasst
    data.autopilot = db->apEngaged.get(); // boolean (brauchen wir den überhaupt? reichen nicht AT/alt_hold/hdg_hold?)
    data.autothrottle = db->apSpeedHoldEngaged.get(); //boolean
    data.alt_hold = db->apALTHoldEngaged.get(); //boolean
    data.hdg_hold = db->apHDGHoldEngaged.get(); //boolean
    data.sim_reset = db->sim_resetted.get();
    
    net.sendData(&data, sizeof(data));
}

void ClientHardware::receiveInfo() {
	recvData data;
    
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data)) {
        std::cout << "Hardware Data Mismatch..." << std::endl;
        return;
    }
    
    std::cout << "Hardware Received " << n << " / " << n << " bytes" << std::endl;

	//put data in database
	db->iFlaps.set(data.flaps); //int
	db->iTrim.set(data.trimmung);
	db->apHding.set(data.heading_set/180*3.14159265); //float
    db->gear_lever.set(data.gear_set);
	db->apEngaged.set(data.autopilot_engaged); //boolean
    db->apSpeed.set(data.speed_set);
    db->apAlt.set(data.alt_set*0.3048);
    db->apSpeedHoldEngaged.set(data.autothrottle_engaged);
	db->apALTHoldEngaged.set(data.alt_hold_engaged); //boolean
	db->apHDGHoldEngaged.set(data.hdg_hold_engaged); //boolean
	db->iAiln.set(data.aileron);
	db->iElev.set(data.elevator);
	db->iRuddr.set(data.rudder);
    db->iThrott_l.set(data.thrust_l);
    db->iThrott_r.set(data.thrust_r);
    
    db->debugOutput();
}