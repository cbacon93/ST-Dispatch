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
    dmcap.gen.head = db->aTHDG.get();
    dmcap.gen.headActTrack = db->aTCRS.get();
    dmcap.gen.headActTrackVis = 1;
    
    //height
    dmcap.gen.alt = db->aIA.get();
    dmcap.gen.altRadAlt = db->aHGT.get();
    dmcap.gen.altBaroRefMode = 1;
    dmcap.gen.altBaroRef = 1013;
    
    if (db->aHGT.get() <= 2500) {
        dmcap.gen.altRadAltVis = 1;
    } else {
        dmcap.gen.altRadAltVis = 0;
    }
    
    //autopilot
    dmcap.gen.targetSpeed = db->apSpeed.get();
    dmcap.gen.altTargetSelAlt = db->apAlt.get();
    dmcap.gen.headSel = db->apHding.get();
    dmcap.gen.headSelVis = 1;
    //dmcap.gen.pfdALTFlagVis = db->apALTHoldEngaged.get();
    //dmcap.gen.pfdSPDFlagVis = db->apSpeedHoldEngaged.get();
    //dmcap.gen.pfdHDGFlagVis = db->apHDGHoldEngaged.get();
    
    //ILS
    dmcap.gen.glsVis = db->ilsAlive.get();
    dmcap.gen.glsIndexVis = db->ilsAlive.get();
    dmcap.gen.locVis = db->ilsAlive.get();
    dmcap.gen.locIndexVis = db->ilsAlive.get();
    dmcap.gen.pfdIlsInfoVis = db->ilsAlive.get();
    dmcap.gen.pfdIlsMsgVis = db->ilsAlive.get();
    dmcap.gen.loc = db->ilsLoc.get();
    dmcap.gen.gls = db->ilsGs.get();
    
    
    //FMA
    FMA fma1;
    memset(&fma1, 0, sizeof(FMA));
    sprintf(fma1.text, "AP1");
    fma1.textVis = db->apEngaged.get();
    
    FMA fma2;
    memset(&fma2, 0, sizeof(FMA));
    sprintf(fma2.text, "ALT");
    fma2.textVis = db->apALTHoldEngaged.get();
    
    FMA fma3;
    memset(&fma3, 0, sizeof(FMA));
    sprintf(fma3.text, "Speed");
    fma3.textVis = db->apSpeedHoldEngaged.get();
    
    FMA fma4;
    memset(&fma4, 0, sizeof(FMA));
    sprintf(fma4.text, "HDG");
    fma4.textVis = db->apHDGHoldEngaged.get();
    
    FMA fma5;
    memset(&fma5, 0, sizeof(FMA));
    sprintf(fma5.text, "ILS");
    fma5.textVis = 0;
    
    FMA fma6;
    memset(&fma6, 0, sizeof(FMA));
    sprintf(fma6.text, "A/THR");
    fma6.textVis = db->apSpeedHoldEngaged.get();
    
    dmcap.gen.fmaVis = 1;
    dmcap.gen.fma[0][0] = fma3;
    dmcap.gen.fma[0][1] = fma2;
    dmcap.gen.fma[0][2] = fma4;
    dmcap.gen.fma[0][4] = fma1;
    dmcap.gen.fma[2][4] = fma6;
    
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