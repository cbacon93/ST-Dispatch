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
bool Networking::initSocket(std::string ip_adress, unsigned int sendport, unsigned int recvport)
{
    //empty data
    bzero(&recvAddr, sizeof(recvAddr));
    bzero(&sendAddr, sizeof(sendAddr));
    
    //input client data
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(recvport);
    recvAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    inet_pton(AF_INET, "0.0.0.0", &recvAddr.sin_addr);
    
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(sendport);
    sendAddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());
    inet_pton(AF_INET, ip_adress.c_str(), &sendAddr.sin_addr);
    
    //create udp sockets
    recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    
    if (bind(recvSocket, (struct sockaddr*)& recvAddr, sizeof(recvAddr)) < 0) {
        std::cerr << "ERROR: Could not bind Socket " << ip_adress << ":" << recvport << std::endl;
        return false;
    }
    
    if (recvSocket < 0 || sendSocket < 0) {
        std::cerr << "ERROR: Could not open Socket " << ip_adress << ":" << recvport << std::endl;
        return false;
    }
    
    return true;
}
#endif


#ifdef __APPLE__
void Networking::closeSocket()
{
    close(recvSocket);
    close(sendSocket);
}
#endif


#ifdef _WIN32
bool Networking::initSocket(std::string ip_adress, unsigned int sendport, unsigned int recvport)
{
    int wsaError = WSAStartup( MAKEWORD(2,2), &wsaData );
    
    if(wsaError)
    {
        std::cerr << "ERROR: wsa Startup error!" << std::endl;
        return false;
    }
        
    //reset client adress struct
    ZeroMemory(&recvAddr, sizeof(recvAddr));
    ZeroMemory(&sendAddr, sizeof(sendAddr));
    
    //settings
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(recvport);
    recvAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(sendport);
    sendAddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());
    
    //create socket
    recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (bind(recvSocket,(SOCKADDR*)&recvAddr,sizeof(SOCKADDR_IN)) < 0) {
        std::cerr << "ERROR: Could not bind Socket " << ip_adress << ":" << recvport << std::endl;
        return false;
    }
    
    if (recvSocket < 0 || sendSocket < 0) {
        std::cerr << "ERROR: Could not open Socket " << ip_adress << ":" << recvport << std::endl;
        return false;
    }
    
    
    return true;
}
#endif



#ifdef _WIN32
void Networking::closeSocket()
{
    closesocket(recvSocket);
    closesocket(sendSocket);
    WSACleanup();
}
#endif


void Networking::sendData(const void* data, unsigned long size)
{
    unsigned long n= sendto(sendSocket, (const char*)data, size, 0, (struct sockaddr *) &sendAddr, sizeof (sendAddr));
    
    if (n <= 0) {
        std::cerr << "ERROR: sending zero bytes" << std::endl;
    }
}


unsigned long Networking::receiveData(void* data, unsigned long size)
{
    socklen_t addLength = sizeof (recvAddr);
    return recvfrom(recvSocket, (char*)data, size, 0, (struct sockaddr *) &recvAddr, &addLength);
}