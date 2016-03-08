//
//  networking.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "networking.hpp"


Networking::Networking()
{
    
}


Networking::~Networking()
{
    
}

#ifdef __APPLE__
bool Networking::initSocket(std::string ip_adress, unsigned int port)
{
    //empty data
    bzero(&clientAddr, sizeof(clientAddr));
    
    //input client data
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = port;
    clientAddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());
    
    //create udp socket
    netSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (netSocket < 0) {
        std::cerr << "ERROR: Could not open Socket " << ip_adress << ":" << port << std::endl;
        return false;
    }
    
    return true;
}
#endif


#ifdef __APPLE__
void Networking::closeSocket()
{
}
#endif


#ifdef _WIN32
bool Networking::initSocket(std::string ip_adress, unsigned int port)
{
    int wsaError = WSAStartup( MAKEWORD(2,2), &wsaDat );
    
    if(wsaError)
    {
        std::cerr << "ERROR: wsa Startup error!" << std::endl;
        return false;
    }
    
    netSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        
    if (netSocket == INVALID_SOCKET)
    {
        std::cerr << "ERROR: socket function failed with error: " << WSAGetLastError() << std::endl;;
        return false;
    }
        
    //reset client adress struct
    ZeroMemory(&clientAddr, sizeof(clientAddr));
    
    //settings
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(port);
    clientAddr.sin_addr.s_addr = inet_addr(ip_adress);
    
    //create socket
    netSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    return true;
}
#endif



#ifdef _WIN32
void Networking::closeSocket()
{
    closesocket(netSocket);
    WSACleanup();
}
#endif


void Networking::sendData(void* data, unsigned int size)
{
    ssize_t n= sendto(netSocket, data, size, 0, (struct sockaddr *) &clientAddr, sizeof (clientAddr));
    
    if (n < 0) {
        std::cerr << "ERROR: sending bytes" << std::endl;
    }
}


long Networking::receiveData(void* data, unsigned int size)
{
    return recvfrom(netSocket, data, size, 0, NULL, NULL);
}