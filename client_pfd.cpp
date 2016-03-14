//
//  client_pfd.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_pfd.hpp"



void ClientPFD::sendInfo() {
    
    dmcap.fplanCnt = 0;
    dmcap.navObjCnt = 0;
    
    dmcap.gen.flightPhase = 5;
    
    dmcap.gen.indAirSpeed = db->vKIAS.get();
    dmcap.gen.grndSpeed = db->vKTGS.get();
    dmcap.gen.vspeed = db->vVS.get();
    dmcap.gen.machVis = 1;
    dmcap.gen.mach = db->vMach.get();
    
    dmcap.gen.pitch = db->aPitch.get();
    dmcap.gen.roll = -db->aRoll.get();
    dmcap.gen.ssIndicationVis = 1;
    dmcap.gen.elCmdSs = db->iElev.get();
    dmcap.gen.aiCmdSs = db->iAiln.get();
    
    dmcap.gen.alt = db->aIA.get()*0.3048;
    dmcap.gen.altRadAlt = db->aHGT.get()*0.3048;
    dmcap.gen.altBaroRefMode = 1;
    dmcap.gen.altBaroRef = 1013;
    dmcap.gen.altRadAltVis = 1;
    
    dmcap.gen.head = db->aTHDG.get();
    dmcap.gen.lat = db->lat.get();
    dmcap.gen.lon = db->lon.get();
    
    dmcap.gen.vspeedCol = (int)(255*255*255* 255 + 255*255* 255 + 255* 0 + 0);
    dmcap.gen.altNumCol = (int)(255*255*255* 255 + 255*255* 255 + 255* 0 + 0);
    dmcap.updateSndBuf();
    
    net.sendData(dmcap.buf,dmcap.getSizeExp());
}


void ClientPFD::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data))
        return;
}