//
//  client_modell.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 17.05.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_modell_hpp
#define client_modell_hpp

#include "client.hpp"

#pragma pack(1)

class ClientModell : public Client {
private:
    //data structures
    struct sendData {
        double throt_c;
        double ze_c;
        double et_c;
        double xi_c;
        double gear_c;
        double flaps_c;
        double speedBrake_c;
        double brake_c;
        double wind_x;
        double wind_y;
        double wind_z;
        double wind_rot_x;
        double wind_rot_y;
        double wind_rot_z;
        double elevation;
        double run;
        double reset;
    };
    
    struct recvData {
        double airspeed;
        double mach;
        double gs;
        double vspeed;
        double alt;
        double lat;
        double lon;
        double roll;
        double pitch;
        double hdg;
        double track;
        double gear_up;
        double gear_dn;
    };
    
public:
    //inherit constructor of base class
    ClientModell(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();
    
};

#endif /* client_modell_hpp */
