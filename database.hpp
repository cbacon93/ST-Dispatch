//
//  database.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include <mutex>
#include <iostream>

/*
 Speichert alle Variablen,
 Enthält Funktionen zum lesen und zum schreiben der Variablen
 Sorgt dafür, dass Variablen nicht gleichzeitig gelesen und geschrieben werden (Mutex)
 Empfehlung: Pro Variable je eine Funktion zum lesen, und eine Funktion zum schreiben
    (Oder Zugriff mit ID)
 
 Klasse wird nur EINMAL instanziert.
 */


//Element der Datenbank - Thread Safe
template <class T>
class DBElement {
private:
    //variablenwert
    T value;
    //sicherungs mutex
    std::mutex mtx;
public:
    DBElement() {
        value = (T) 0;
    }
    
    void set(T _newvalue) {
        //mutex lock - not read and write at the same time
        mtx.lock();
        value = _newvalue;
        mtx.unlock();
    }
    
    T get() {
        //mutex lock - not read and write at the same time
        mtx.lock();
        T tmp = value;
        mtx.unlock();
        //return interrupts function - so we need a tmp variable
        return tmp;
    }
};



//Datenbankklasse
class Database {
public:
    void initData();
    void debugOutput();
    
    DBElement<int> exampleCntr;
    
    //sim flags
    DBElement<bool> sim_running;
    DBElement<bool> sim_resetted;

    //speed in knots
    DBElement<double> vKIAS;
    DBElement<double> vKTAS;
    DBElement<double> vKTGS;
    DBElement<double> vMach;
    DBElement<double> vVS; //m/s
    
    //wind
    DBElement<double> vWind; //knots
    DBElement<double> dirWind; //rad
    DBElement<double> xWind; // m/s
    DBElement<double> yWind; //
    DBElement<double> zWind; //
    DBElement<double> xRotWind;
    DBElement<double> yRotWind;
    DBElement<double> zRotWind;
    
    //input
    DBElement<double> iAiln; // -1 .. 1
    DBElement<double> iElev;
    DBElement<double> iRuddr;
    DBElement<double> iFlaps; // 0, 1, 2, 3, 4
    DBElement<double> iTrim; // -1 .. 1
    DBElement<double> iThrott_l; // -0.6 .. 1
    DBElement<double> iThrott_r; //
    DBElement<double> iBrake; // 0
    DBElement<double> iSpeedBrake; // 0
    
    //gear
    DBElement<bool> gear_lever;
    DBElement<double> gear_pos; // 0 .. 1
    
    //attitude
    DBElement<double> aPitch; //rad
    DBElement<double> aRoll; //rad
    DBElement<double> aTHDG; //rad
    DBElement<double> aTCRS; //rad
    DBElement<double> aMHDG; //rad
    DBElement<double> lat; //deg
    DBElement<double> lon; //deg
    DBElement<double> elevation; //m
    
    //altitudes
    DBElement<double> aHGT; //m
    DBElement<double> aPA; //m
    DBElement<double> aIA; //m
    
    //autopilot
    DBElement<bool> apEngaged;
    DBElement<bool> apHDGHoldEngaged;
    DBElement<bool> apALTHoldEngaged;
    DBElement<bool> apSpeedHoldEngaged;
    DBElement<double> apSpeed; //kts
    DBElement<double> apHding; //rad
    DBElement<double> apVvi; //m/s
    DBElement<double> apAlt; //m
    
    //autopilot button
    DBElement<bool> apEngagedButton;
    DBElement<bool> apHDGHoldEngagedButton;
    DBElement<bool> apALTHoldEngagedButton;
    DBElement<bool> apSpeedHoldEngagedButton;
    
    //ILS
    DBElement<bool> ilsAlive;
    DBElement<double> ilsGs; //rad
    DBElement<double> ilsLoc; //rad
};



#endif /* database_hpp */
