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
		float flaps;
		double trimmung;
		double heading_set;
		long gear_set;
		long autopilot_engaged;
		float speed_set;
		float alt_set;
		long autothrottle_engaged;
		long alt_hold_engaged;
		long hdg_hold_engaged;
		float aileron;
		float elevator;
		float rudder;

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