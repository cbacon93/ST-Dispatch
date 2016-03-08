//
//  networking.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef networking_hpp
#define networking_hpp




/*
 Übernimmt das Networking
 Verbindungsaufbau, senden und empfangen
 Platform independent!
 
 Pro Client eine Instanz
 */

//Include the essential header-files
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#ifdef __APPLE__
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#endif

#include <iostream>
#include <string>


class Networking
{
private:
#ifdef _WIN32
    SOCKET netSocket;
    WSADATA wsaData;
#endif
    
#ifdef __APPLE__
    int netSocket;
#endif
    
    sockaddr_in clientAddr;
    
public:
    Networking();
    ~Networking();
    
    bool initSocket(std::string ip_adress, unsigned int port);
    void sendData(void* data, unsigned int size);
    long receiveData(void* data, unsigned int size);
    void closeSocket();
};


#endif /* networking_hpp */
