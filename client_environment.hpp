//
//  client_environment.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 11.05.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_environment_hpp
#define client_environment_hpp

#include "client.hpp"

class ClientEnvironment : public Client {
private:
    //data structures
    struct sendData {
        double lat;
        double lon;
        double talt;
        double phi;
        double theta;
        double psi;
    };
    
    struct recvData {
        double xwind;
        double ywind;
        double zwind;
        double elevation;
        double winddir;
        double windspeed;
    };
    
    
public:
    //inherit constructor of base class
    ClientEnvironment(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();

};

#endif /* client_environment_hpp */