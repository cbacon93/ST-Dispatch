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
    
    unsigned long n = net.receiveData(buffer, 512);
    unsigned int dn = 0;
    
    //accept data
    char header[5];
    memcpy(header, buffer, 5);                              dn += 5;
    header[4] = '\0';
    std::string cmp = "DATA";
    
    if (cmp.compare(header) != 0 || n > 512)
        return;
    
    do {
    //get index
    int index;
    memcpy(&index, buffer + dn, 4);                         dn += 4;
    
    //get data
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
            memcpy(&data4, buffer + dn, sizeof(data4));      dn += sizeof(data4);
            db->vMach.set(data4.mach);
            db->vVS.set(data4.vvi);
            break;
        case 8:
            recvData8 data8;
            memcpy(&data8, buffer + dn, sizeof(data8));      dn += sizeof(data8);
            db->iAiln.set(data8.ailn);
            db->iElev.set(data8.elev);
            db->iRuddr.set(data8.ruddr);
            break;
        case 17:
            recvData17 data17;
            memcpy(&data17, buffer + dn, sizeof(data17));      dn += sizeof(data17);
            db->aPitch.set(data17.pitch/180.f*3.141f);
            db->aRoll.set(data17.roll/180.f*3.141f);
            db->aTHDG.set(data17.thding/180.f*3.141f);
            db->aMHDG.set(data17.mhding/180.f*3.141f);
            break;
        case 20:
            recvData20 data20;
            memcpy(&data20, buffer + dn, sizeof(data20));      dn += sizeof(data20);
            db->aHGT.set(data20.altagl);
            db->aIA.set(data20.altind);
            db->aPA.set(data20.altmsl);
            db->lat.set(data20.lat);
            db->lon.set(data20.lon);
    }
    } while(dn < n);

}