//
//  client_pfd.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "client_pfd.hpp"

struct charstr {
    char x[5];
};


void ClientPFD::sendInfo() {
    DMCAP dmcap;
    
    memset(&dmcap, 0, sizeof(DMCAP));
    
    dmcap.header.version = 2.0f;
    dmcap.header.size = sizeof(DMCAP);
    dmcap.header.reply = 0;
    dmcap.header.objCnt = 1;
    
    dmcap.object.objHeader.typ = 0;
    dmcap.object.objHeader.len = sizeof(DMCAPObject);
    dmcap.object.objHeader.index = 1;
    dmcap.object.objHeader.setup = 0;
    
    net.sendData(&dmcap, sizeof(dmcap));
}


void ClientPFD::receiveInfo() {
    recvData data;
    unsigned long n = net.receiveData(&data, sizeof(data));
    
    //corrupt data -> abort
    if (n != sizeof(data))
        return;
}