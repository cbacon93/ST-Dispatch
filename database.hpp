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

    //speed
    DBElement<double> vKIAS;
    DBElement<double> vKTAS;
    DBElement<double> vKTGS;
    DBElement<double> vMach;
    DBElement<double> vVS;
    
    //wind
    DBElement<double> vWind;
    DBElement<double> dirWind;
    DBElement<double> xWind; //u
    DBElement<double> yWind; //v
    DBElement<double> zWind; //w
    DBElement<double> xRotWind;
    DBElement<double> yRotWind;
    DBElement<double> zRotWind;
    
    //input
    DBElement<double> iAiln;
    DBElement<double> iElev;
    DBElement<double> iRuddr;
    DBElement<long>   iFlaps;
    DBElement<double> iTrim;
    DBElement<double> iThrott;
    DBElement<double> iBreak;
    DBElement<double> iSpeedBreak;
    
    //gear
    DBElement<bool> gear_lever;
    DBElement<bool> gear_down;
    DBElement<bool> gear_up;
    
    //attitude
    DBElement<double> aPitch;
    DBElement<double> aRoll;
    DBElement<double> aTHDG;
    DBElement<double> aTCRS;
    DBElement<double> aMHDG;
    DBElement<double> lat;
    DBElement<double> lon;
    DBElement<double> elevation;
    
    //altitudes
    DBElement<double> aHGT;
    DBElement<double> aPA;
    DBElement<double> aIA;
    
    //autopilot
    DBElement<bool> apEngaged;
    DBElement<bool> apHDGHoldEngaged;
    DBElement<bool> apALTHoldEngaged;
    DBElement<bool> apSpeedHoldEngaged;
    DBElement<double> apSpeed;
    DBElement<double> apHding;
    DBElement<double> apVvi;
    DBElement<double> apAlt;
    
    //ILS
    DBElement<bool> ilsAlive;
    DBElement<double> ilsGs;
    DBElement<double> ilsLoc;
};



#endif /* database_hpp */
