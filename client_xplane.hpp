//
//  client_xplane.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_xplane_hpp
#define client_xplane_hpp

#include <string>
#include "client.hpp"

class ClientXplane : public Client {
private:
    //data structures
    
    struct recvData3 {
        float vIndKias;
        float vIndKeas;
        float vTrueKtas;
        float vTrueKtgs;
        float none1;
        float vIndMph;
        float vTrueMphas;
        float vTrueMphgs;
    };
    
    struct recvData4 {
        float mach;
        float none1;
        float vvi;
        float none2;
        float gloadn;
        float gloada;
        float gloads;
    };
    
    struct recvData8 {
        float elev;
        float ailn;
        float ruddr;
    };
    
    struct recvData17 {
        float pitch;
        float roll;
        float thding;
        float mhding;
    };
    
    struct recvData20 {
        float lat;
        float lon;
        float altmsl;
        float altagl;
        float onrwy;
        float altind;
        float lats;
        float lonw;
    };
    
    struct recvData118 {
        float speed;
        float hding;
        float vvi;
        float alt;
        float vnavAlt;
        float useAlt;
        float syncRoll;
        float syncPitch;
    };
    
public:
    //inherit constructor of base class
    ClientXplane(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void receiveInfo();
    
};


#endif /* client_xplane_hpp */
