//
//  client_pfd.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_pfd.hpp"



void ClientPFD::sendInfo() {
    //set all data from database
    dmcap.fplanCnt = 0;
    dmcap.navObjCnt = 0;
    
    dmcap.gen.flightPhase = 0;
    
    //speeds
    dmcap.gen.indAirSpeed = db->vKIAS.get();
    dmcap.gen.grndSpeed = db->vKTGS.get();
    dmcap.gen.vspeed = db->vVS.get();
    dmcap.gen.machVis = 1;
    dmcap.gen.mach = db->vMach.get();
    
    //attitudes
    dmcap.gen.pitch = db->aPitch.get();
    dmcap.gen.roll = -db->aRoll.get();
    dmcap.gen.ssIndicationVis = 1;
    dmcap.gen.elCmdSs = db->iElev.get();
    dmcap.gen.aiCmdSs = db->iAiln.get();
    dmcap.gen.head = db->aMHDG.get();
    
    //height
    dmcap.gen.alt = db->aIA.get();
    dmcap.gen.altRadAlt = db->aHGT.get();
    dmcap.gen.altBaroRefMode = 1;
    dmcap.gen.altBaroRef = 1013;
    dmcap.gen.altRadAltVis = 1;
    
    //autopilot
    dmcap.gen.targetSpeed = db->apSpeed.get();
    dmcap.gen.altTargetSelAlt = db->apAlt.get();
    dmcap.gen.headSel = db->apHding.get();
    dmcap.gen.headSelVis = 1;
    
    //misc
    dmcap.gen.lat = db->lat.get();
    dmcap.gen.lon = db->lon.get();
    
    //set colors as RGBA
    unsigned char * vspeedCol = (unsigned char*)&(dmcap.gen.vspeedCol);
    vspeedCol[0] = 0;   //r
    vspeedCol[1] = 255; //g
    vspeedCol[2] = 0;   //b
    vspeedCol[3] = 255; //a

    unsigned char * altnumCol = (unsigned char*)&(dmcap.gen.altNumCol);
    altnumCol[0] = 0;
    altnumCol[1] = 255;
    altnumCol[2] = 0;
    altnumCol[3] = 255;
    
    dmcap.gen.altTargetCol =dmcap.gen.altNumCol;
    
    //build send buffer and send data
    dmcap.updateSndBuf();
    net.sendData(dmcap.buf,dmcap.getSizeExp());
}


void ClientPFD::receiveInfo() {
    //nothing to do
    
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data))
        return;
}