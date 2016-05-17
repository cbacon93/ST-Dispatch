//
//  client_example.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 09.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_example_hpp
#define client_example_hpp

#include "client.hpp"

#pragma pack(1)

class ClientExample : public Client {
private:
    //data structures
    struct sendData {
        unsigned char running;
        unsigned char reset;
        int counter;
    };
    
    struct recvData {
        unsigned char running;
        unsigned char reset;
        int counter;
    };
    
public:
    //inherit constructor of base class
    ClientExample(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
        Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();

};

#endif /* client_example_hpp */
