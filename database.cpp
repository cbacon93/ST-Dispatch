//
//  database.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "database.hpp"


//to be implemented if necessary
void Database::initData() {
    this->lat.set(52.191);
    this->lon.set(10.331);
    
    this->gear_lever.set(1);
    this->iThrott_l.set(0);
    this->iThrott_r.set(0);
    
    this->aTHDG.set(0);
    this->apEngaged.set(true);
}


void Database::debugOutput() {
    std::cout << "vKIAS: " << vKIAS.get() << std::endl;
    std::cout << "vMach: " << vMach.get() << std::endl;
    std::cout << "vVS: " << vVS.get() << std::endl;
    std::cout << "aPA: " << aPA.get() << std::endl;
    std::cout << "lat: " << lat.get() << std::endl;
    std::cout << "lon: " << lon.get() << std::endl;
    std::cout << "aRoll: " << aRoll.get() << std::endl;
    std::cout << "aPitch: " << aPitch.get() << std::endl;
    std::cout << "aTHDG: " << aTHDG.get() << std::endl;
    std::cout << "gear_up: " << gear_up.get() << std::endl;
    std::cout << "gear_down: " << gear_down.get() << std::endl;
}