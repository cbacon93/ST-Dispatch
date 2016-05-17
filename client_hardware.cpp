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
	data.gear_down = db->gear_down.get(); //2 doubles zu bool zusammengefasst
    data.autopilot = db->apEngaged.get(); // boolean (brauchen wir den überhaupt? reichen nicht AT/alt_hold/hdg_hold?)
    data.autothrottle = db->apSpeedHoldEngaged.get(); //boolean
    data.alt_hold = db->apALTholdEngaged.get(); //boolean
    data.hdg_hold = db->apHDGholdEngaged.get(); //boolean
  
    
    net.sendData(&data, sizeof(data));
}

void ClientHardware::receiveInfo() {
	recvData data;

	//put data in database
	db.iFlaps.set() = data.flaps; //int
	db.iTrim.set() = data.trimmung;
	db.apHding.set() = data.heading; //float
	db.gear_down.set() = data.gear; //boolean
	db.apEngaged.set() = data.autopilot; //boolean
	db.apSpeed.set() = data.vIAS;
	db.apAlt.set() = data.alt_set;
	db.apSpeedHoldEngaged.set() = data.autothrottle; //boolean
	db.apALTHoldEngaged.set() = data.alt_hold; //boolean
	db.apHDGHoldEngaged.set() = data.hdg_hold; //boolean
	db.iAiln.set() = data.aileron;
	db.iElev.set() = data.elevator;
	db.iRuddr.set() = data.rudder;

	unsigned long n = net.receiveData(&data, sizeof(data));

	//corrupt data -> abort
	if (n != sizeof(data))
		return;
}