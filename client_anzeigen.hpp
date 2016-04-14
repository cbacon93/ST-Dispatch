//
//  client_anzeigen.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.04.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_anzeigen_hpp
#define client_anzeigen_hpp

#include "client.hpp"
#pragma pack(1)

class ClientAnzeigen : public Client {
private:
    //data structures
    struct sendData {
        double latitude;
        double longitude;
        double heading;
        double course;
        double groundspeed;
        double trueairspeed;
        double winddir;
        double windspeed;
        unsigned char sim_reset;
    };
    
public:
    //inherit constructor of base class
    ClientAnzeigen(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
};

#endif /* client_anzeigen_hpp */