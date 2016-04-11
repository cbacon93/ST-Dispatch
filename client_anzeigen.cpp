//
//  client_anzeigen.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.04.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_anzeigen.hpp"


void ClientAnzeigen::sendInfo() {
    sendData data;
    
    //take data from database
    data.latitude = db->lat.get();
    data.longitude = db->lon.get();
    data.heading = db->aTHDG.get();
    data.course = db->aTCRS.get();
    data.groundspeed = db->vKTGS.get();
    data.trueairspeed = db->vKTAS.get();
    data.winddir = db->dirWind.get();
    data.windspeed = db->vWind.get();
    data.sim_reset = db->sim_resetted.get();
    
    
    net.sendData(&data, sizeof(data));
}
