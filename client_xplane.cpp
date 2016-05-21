//
//  client_xplane.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_xplane.hpp"



void ClientXplane::receiveInfo() {
    unsigned char buffer[512];
    
    //receive data
    unsigned long n = net.receiveData(buffer, 512);
    unsigned int dn = 0;
    
    //get header
    char header[5];
    memcpy(header, buffer, 5);                                  dn += 5;
    header[4] = '\0';
    
    //header must equal "DATA"
    std::string cmp = "DATA";
    if (cmp.compare(header) != 0 || n > 512)
        return;
    
    //process every information by index
    do {
        //get index
        int index;
        memcpy(&index, buffer + dn, 4);                         dn += 4;
        
        //get data by index
        switch(index) {
            case 3:
                recvData3 data3;
                memcpy(&data3, buffer + dn, sizeof(data3));     dn += sizeof(data3);
                db->vKIAS.set(data3.vIndKias);
                db->vKTAS.set(data3.vTrueKtas);
                db->vKTGS.set(data3.vTrueKtgs);
                break;
            case 4:
                recvData4 data4;
                memcpy(&data4, buffer + dn, sizeof(data4));     dn += sizeof(data4);
                db->vMach.set(data4.mach);
                
                if (data4.vvi != -999.f)
                    db->vVS.set(data4.vvi/196.85f);
                else
                    db->vVS.set(0);
                
                break;
                
            case 5:
                recvData5 data5;
                memcpy(&data5, buffer + dn, sizeof(data5));     dn += sizeof(data5);
                db->vWind.set(data5.windspeed);
                db->dirWind.set(data5.winddir/180.f*3.14159265f);
                break;
            case 8:
                recvData8 data8;
                memcpy(&data8, buffer + dn, sizeof(data8));     dn += sizeof(data8);
                db->iAiln.set(data8.ailn);
                db->iElev.set(data8.elev);
                db->iRuddr.set(data8.ruddr);
                break;
            case 17:
                recvData17 data17;
                memcpy(&data17, buffer + dn, sizeof(data17));   dn += sizeof(data17);
                db->aPitch.set(data17.pitch/180.f*3.14159265f);
                db->aRoll.set(data17.roll/180.f*3.14159265f);
                db->aTHDG.set(data17.thding/180.f*3.14159265f);
                db->aMHDG.set(data17.mhding/180.f*3.14159265f);
                break;
            case 18:
                recvData18 data18;
                memcpy(&data18, buffer + dn, sizeof(data18));   dn += sizeof(data18);
                db->aTCRS.set(data18.hpath/180.f*3.14159265f);
                break;
            case 20:
                recvData20 data20;
                memcpy(&data20, buffer + dn, sizeof(data20));   dn += sizeof(data20);
                db->aHGT.set(data20.altagl*0.3048);
                db->aIA.set(data20.altind*0.3048);
                db->aPA.set(data20.altmsl*0.3048);
                db->lat.set(data20.lat);
                db->lon.set(data20.lon);
                db->elevation.set(db->aPA.get() - db->aHGT.get());
                break;
            case 108:
                recvData108 data108;
                memcpy(&data108, buffer + dn, sizeof(data108));   dn += sizeof(data108);
                
                if (data108.fdirmode == 2.0f) {
                    db->apEngaged.set(true);
                } else {
                    db->apEngaged.set(false);
                }
                
                break;
            case 116:
                recvData116 data116;
                memcpy(&data116, buffer + dn, sizeof(data116));   dn += sizeof(data116);
                break;
            case 117:
                recvData117 data117;
                memcpy(&data117, buffer + dn, sizeof(data117));   dn += sizeof(data117);
                
                if (data117.autothrot == 1.0f) {
                    db->apSpeedHoldEngaged.set(true);
                } else {
                    db->apSpeedHoldEngaged.set(false);
                }
                
                if (data117.modehding == 1.0f) {
                    db->apHDGHoldEngaged.set(true);
                } else {
                    db->apHDGHoldEngaged.set(false);
                }
                
                if (data117.modealt == 6.0f) {
                    db->apALTHoldEngaged.set(true);
                } else {
                    db->apALTHoldEngaged.set(false);
                }
                
                break;
            case 118:
                recvData118 data118;
                memcpy(&data118, buffer + dn, sizeof(data118));   dn += sizeof(data118);
                db->apSpeed.set(data118.speed);
                db->apHding.set(data118.hding/180.f*3.14159265f);
                db->apAlt.set(data118.alt*0.3048);
                db->apVvi.set(data118.vvi/196.85);
        }
    } while(dn < n); //no bytes left
}