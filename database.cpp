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
    this->gear_pos.set(1);
    this->gear_lever.set(1);
    this->iFlaps.set(0);
    
    this->apHding.set(4.538);
    this->apAlt.set(1524);
    this->apSpeed.set(260);
    
    //start data
    this->lat.set(52.319800); // 52.3203N
    this->lon.set(10.567241); // 10.5754E
    
    this->iThrott_l.set(0);
    this->iThrott_r.set(0);
    
    this->aTHDG.set(4.62135);
    this->aMHDG.set(4.62135 - 0.0175);
    this->elevation.set(90);
    this->aPA.set(92);
    this->aIA.set(92);
    this->aHGT.set(2);
}


void Database::debugOutput() {
    std::cout << "KIAS: " << vKIAS.get() << std::endl;
    std::cout << "Mach: " << vMach.get() << std::endl;
    std::cout << "VS: " << vVS.get() << std::endl;
    std::cout << "PALT: " << aPA.get() << std::endl;
    std::cout << "IALT: " << aIA.get() << std::endl;
    std::cout << "ELEV: " << elevation.get() << std::endl;
    std::cout << "lat: " << lat.get() << std::endl;
    std::cout << "lon: " << lon.get() << std::endl;
    std::cout << "aRoll: " << aRoll.get() << std::endl;
    std::cout << "aPitch: " << aPitch.get() << std::endl;
    std::cout << "THDG: " << aTHDG.get() << std::endl;
    std::cout << "MHDG: " << aMHDG.get() << std::endl;
    std::cout << "HGT: " << aHGT.get() << std::endl;
    std::cout << "Stick X: " << iElev.get() << std::endl;
    std::cout << "Stick Y: " << iAiln.get() << std::endl;
    std::cout << "Stick Z: " << iRuddr.get() << std::endl;
    std::cout << "gear_pos: " << gear_pos.get() << std::endl;
    std::cout << "gear_lever: " << gear_lever.get() << std::endl;
    std::cout << "AP: " << apEngaged.get() << std::endl;
    std::cout << "Button AP: " << apEngagedButton.get() << std::endl;
    std::cout << "AT: " << apSpeedHoldEngaged.get() << std::endl;
    std::cout << "Button AT: " << apSpeedHoldEngagedButton.get() << std::endl;
    std::cout << "AP HDG: " << apHDGHoldEngaged.get() << std::endl;
    std::cout << "Button AP HDG: " << apHDGHoldEngagedButton.get() << std::endl;
    std::cout << "AP ALT: " << apALTHoldEngaged.get() << std::endl;
    std::cout << "Button AP ALT: " << apALTHoldEngagedButton.get() << std::endl;
    std::cout << "Thrust R: " << iThrott_r.get() << std::endl;
    std::cout << "Thrust L: " << iThrott_l.get() << std::endl;
}