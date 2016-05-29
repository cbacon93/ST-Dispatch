//
//  loader.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 29.05.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef loader_hpp
#define loader_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


using namespace std;


struct ConnectionData {
    string ip;
    int port_send;
    int port_receive;
    
    ConnectionData(string _ip, int _port_send, int _port_receive) {
        ip = _ip;
        port_send = _port_send;
        port_receive = _port_receive;
    }
    
    ConnectionData() {
    }
};


class Loader {
private:
    map<string, ConnectionData> connData;
    
    vector<string> explodeString(string line) {
        vector<string> ret;
        
        size_t place1 = line.find_first_of("=");
        size_t place2 = line.find_first_of(":");
        size_t place3 = line.find_last_of(":");
        
        ret.push_back(line.substr(0, place1));
        ret.push_back(line.substr(place1+1, place2-place1-1));
        ret.push_back(line.substr(place2+1, place3-place2-1));
        ret.push_back(line.substr(place3+1, line.length()-place3));
        
        return ret;
    }
public:
    Loader(string filename) {
        ifstream file(filename);
        
        while(!file.eof())
        {
            char line[256];
            file.getline(line, sizeof(line));
            
            
            vector<string> info = explodeString(line);
            
            //cout << "Gruppe: " << info[0] << " - Ip: " << info[1] << endl;
            
            connData.emplace(info[0], ConnectionData(info[1], stoi(info[2]), stoi(info[3])));
        }
        
        file.close();
    }
    
    
    ConnectionData * get(string group) {
        return &(connData[group]);
    }
};


/*int main() {
    
    Loader loader("settings.cnf");
    cout << loader.get("Anzeigen")->ip << " " << loader.get("Anzeigen")->port_send << " " << loader.get("Anzeigen")->port_receive << endl;
    return 0;
}*/

#endif /* loader_hpp */
