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
    dmcap.gen.indAirSpeed = 100;
    dmcap.gen.grndSpeed = 100;
    dmcap.gen.pitch = 0.18;
    dmcap.gen.roll = 0;
    dmcap.gen.alt = db->altitude.get();
    dmcap.gen.altBaroRefMode = 1;
    dmcap.gen.altBaroRef = 1013;
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