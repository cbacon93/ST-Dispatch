//
//  client_pfd.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_pfd_hpp
#define client_pfd_hpp

#include "client.hpp"
#include "A320DMCAP.h"

class ClientPFD : public Client {
private:
    //data structures
    A320DMCAP dmcap;
    
    struct recvData {
        int dummy;
    };
    
public:
    //inherit constructor of base class
    ClientPFD(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort)
    {
    }
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();
    
};

#endif /* client_pfd_hpp */
