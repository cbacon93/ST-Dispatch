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
    //dmcap.gen.vspeedDigiVis = 1; //digital vspeed visible
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
    dmcap.gen.headTruVis = 1;
    dmcap.gen.headActTrackVis = 1;
    dmcap.gen.pitchProtMode = 1;
    dmcap.gen.rollProtMode = 1;
    
    //height
    dmcap.gen.alt = db->aIA.get();
    dmcap.gen.altRadAlt = db->aHGT.get();
    dmcap.gen.altBaroRefMode = 1;
    dmcap.gen.altTargetMode = 1;
    dmcap.gen.altBaroRef = 1013;
    dmcap.gen.altLandElev = db->elevation.get();
    dmcap.gen.altGroundRef = db->aHGT.get();
    
    if (db->aHGT.get() <= 2500*0.3048) {
        dmcap.gen.altRadAltVis = 1;
        dmcap.gen.altLandElevVis = 1;
        dmcap.gen.altGroundRefVis = 1;
    } else {
        dmcap.gen.altRadAltVis = 0;
        dmcap.gen.altLandElevVis = 0;
        dmcap.gen.altGroundRefVis = 0;
    }
    
    
    //SPEED CONFIG
    //flaps max speed
    switch((int)db->iFlaps.get()) {
        case(0):
            dmcap.gen.maxAllowSpeed = 340;
            dmcap.gen.maxAllowSpeedVis = 1;
            
            dmcap.gen.alphaMaxSpeed = 220;
            dmcap.gen.alphaMaxSpeedVis = 1;
            dmcap.gen.alphaProtSpeed = 228;
            dmcap.gen.alphaProtSpeedVis = 1;
            dmcap.gen.minSelSpeed = 233;
            dmcap.gen.minSelSpeedVis = 1;
            
            dmcap.gen.maxFlapExtNextSpeedVis = 1;
            dmcap.gen.maxFlapExtNextSpeed = 263;
            dmcap.gen.minFlapRetractSpeedVis = 0;
            break;
        case(1):
            dmcap.gen.maxAllowSpeed = 263;
            dmcap.gen.maxAllowSpeedVis = 1;
            
            dmcap.gen.alphaMaxSpeed = 183;
            dmcap.gen.alphaMaxSpeedVis = 1;
            dmcap.gen.alphaProtSpeed = 190;
            dmcap.gen.alphaProtSpeedVis = 1;
            dmcap.gen.minSelSpeed = 195;
            dmcap.gen.minSelSpeedVis = 1;
            
            dmcap.gen.maxFlapExtNextSpeedVis = 1;
            dmcap.gen.maxFlapExtNextSpeed = 220;
            dmcap.gen.minFlapRetractSpeedVis = 1;
            dmcap.gen.minFlapRetractSpeed = 233;
            break;
        case(2):
            dmcap.gen.maxAllowSpeed = 220;
            dmcap.gen.maxAllowSpeedVis = 1;
            
            dmcap.gen.alphaMaxSpeed = 150;
            dmcap.gen.alphaMaxSpeedVis = 1;
            dmcap.gen.alphaProtSpeed = 157;
            dmcap.gen.alphaProtSpeedVis = 1;
            dmcap.gen.minSelSpeed = 162;
            dmcap.gen.minSelSpeedVis = 1;
            
            dmcap.gen.maxFlapExtNextSpeedVis = 1;
            dmcap.gen.maxFlapExtNextSpeed = 196;
            dmcap.gen.minFlapRetractSpeedVis = 1;
            dmcap.gen.minFlapRetractSpeed = 195;
            break;
        case(3):
            dmcap.gen.maxAllowSpeed = 196;
            dmcap.gen.maxAllowSpeedVis = 1;
            
            dmcap.gen.alphaMaxSpeed = 124;
            dmcap.gen.alphaMaxSpeedVis = 1;
            dmcap.gen.alphaProtSpeed = 131;
            dmcap.gen.alphaProtSpeedVis = 1;
            dmcap.gen.minSelSpeed = 136;
            dmcap.gen.minSelSpeedVis = 1;
            
            dmcap.gen.maxFlapExtNextSpeedVis = 1;
            dmcap.gen.maxFlapExtNextSpeed = 182;
            dmcap.gen.minFlapRetractSpeedVis = 1;
            dmcap.gen.minFlapRetractSpeed = 162;
            break;
        case(4):
            dmcap.gen.maxAllowSpeed = 182;
            dmcap.gen.maxAllowSpeedVis = 1;
            
            dmcap.gen.alphaMaxSpeed = 110;
            dmcap.gen.alphaMaxSpeedVis = 1;
            dmcap.gen.alphaProtSpeed = 117;
            dmcap.gen.alphaProtSpeedVis = 1;
            dmcap.gen.minSelSpeed = 125;
            dmcap.gen.minSelSpeedVis = 1;
            
            dmcap.gen.maxFlapExtNextSpeedVis = 0;
            dmcap.gen.minFlapRetractSpeedVis = 1;
            dmcap.gen.minFlapRetractSpeed = 136;
            break;
    }
    
    //max gear speed
    if (db->gear_pos.get() > 0 && dmcap.gen.maxAllowSpeed > 250) {
        dmcap.gen.maxAllowSpeed = 250;
        dmcap.gen.maxAllowSpeedVis = 1;
    }
    
    
    //low speed v1 and rotating speed
    if (db->vKIAS.get() < 170 && db->aHGT.get() <= 5) {
        dmcap.gen.rotSpeed = 160;
        dmcap.gen.rotSpeedVis = 1;
        dmcap.gen.decisionSpeed = 120;
        dmcap.gen.decisionSpeedVis = 1;
        
        dmcap.gen.alphaMaxSpeedVis = 0;
        dmcap.gen.alphaProtSpeedVis = 0;
        dmcap.gen.minSelSpeedVis = 0;
        dmcap.gen.maxFlapExtNextSpeedVis = 0;
        dmcap.gen.minFlapRetractSpeedVis = 0;
    } else {
        dmcap.gen.rotSpeedVis = 0;
        dmcap.gen.decisionSpeedVis = 0;
    }
    //SPEED CONFIG END
    
    //autopilot
    dmcap.gen.targetSpeed = db->apSpeed.get();
    dmcap.gen.altTargetSelAlt = db->apAlt.get();
    dmcap.gen.altTargetSelFl = db->apAlt.get();
    dmcap.gen.headSel = db->apHding.get();
    dmcap.gen.headSelVis = 1;
    
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
    fma5.textVis = db->ilsAlive.get();
    
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
    vspeedCol[0] = 000; //b
    vspeedCol[1] = 255; //g
    vspeedCol[2] = 000; //r
    vspeedCol[3] = 255; //a

    unsigned char * altwinCol = (unsigned char*)&(dmcap.gen.altWinCol);
    altwinCol[0] = 000; //b
    altwinCol[1] = 255; //g
    altwinCol[2] = 255; //r
    altwinCol[3] = 255; //a
    
    unsigned char * altselCol = (unsigned char*)&(dmcap.gen.altTargetCol);
    altselCol[0] = 255; //b
    altselCol[1] = 175; //g
    altselCol[2] = 000; //r
    altselCol[3] = 255; //a
    
    dmcap.gen.altNumCol = dmcap.gen.vspeedCol;
    
    
    
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