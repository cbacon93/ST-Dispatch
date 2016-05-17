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

#pragma pack(1)

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
        float none3;
    };
    
    struct recvData5 {
        float slprs;
        float sltmp;
        float none1;
        float windspeed;
        float winddir;
        float trb;
        float prec;
        float hail;
    };
    
    struct recvData8 {
        float elev;
        float ailn;
        float ruddr;
        float none1;
        float none2;
        float none3;
        float none4;
        float none5;
    };
    
    struct recvData17 {
        float pitch;
        float roll;
        float thding;
        float mhding;
        float none1;
        float none2;
        float none3;
        float none4;
    };
    
    struct recvData18 {
        float alpha;
        float beta;
        float hpath;
        float vpath;
        float none1;
        float none2;
        float none3;
        float slip;
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
    
    struct recvData108 {
        float ap;
        float fdirmode;
        float fdirpitch;
        float fdirroll;
        float none1;
        float hudpower;
        float hudbrite;
        float none2;
    };
    
    struct recvData116 {
        float navarm;
        float altarm;
        float apparm;
        float vnavenab;
        float vnavarm;
        float vnavtime;
        float gpenab;
        float apptyp;
    };
    
    struct recvData117 {
        float autothrot;
        float modehding;
        float modealt;
        float none1;
        float bac;
        float app;
        float none2;
        float sync;
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
