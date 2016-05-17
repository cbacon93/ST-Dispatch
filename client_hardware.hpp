//
//  client_hardware.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.04.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_hardware_hpp
#define client_hardware_hpp

#include "client.hpp"
#pragma pack(1)

class ClientHardware : public Client {
private:
    //data structures
    struct sendData {
        double gear_up;
        double gear_down;
        double autopilot;
        double autothrottle;
        double alt_hold;
        double hdg_hold;
        
    };
    
	struct recvData {
		double flaps;
		double trimmung;
		double heading_set;
		double gear_set;
		double autopilot_engaged;
		double speed_set;
		double alt_set;
		double autothrottle_engaged;
		double alt_hold_engaged;
		double hdg_hold_engaged;
		double aileron;
		double elevator;
		double rudder;
	};

public:
    //inherit constructor of base class
     ClientHardware(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();
};

#endif /* client_hardware_hpp */