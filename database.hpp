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
    
    DBElement<int> exampleCntr;
    
    //sim flags
    DBElement<bool> sim_running;
    DBElement<bool> sim_resetted;

    //speed
    DBElement<float> vKIAS;
    DBElement<float> vKTAS;
    DBElement<float> vKTGS;
    DBElement<float> vMach;
    DBElement<float> vVS;
    
    //input
    DBElement<float> iAiln;
    DBElement<float> iElev;
    DBElement<float> iRuddr;
    
    //attitude
    DBElement<float> aPitch;
    DBElement<float> aRoll;
    DBElement<float> aTHDG;
    DBElement<float> aMHDG;
    DBElement<float> lat;
    DBElement<float> lon;
    
    //altitudes
    DBElement<float> aHGT;
    DBElement<float> aPA;
    DBElement<float> aIA;
    
    //autopilot
    DBElement<float> apSpeed;
    DBElement<float> apHding;
    DBElement<float> apVvi;
    DBElement<float> apAlt;
};



#endif /* database_hpp */
