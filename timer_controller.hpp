//
//  timer_controller.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 09.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef timer_controller_hpp
#define timer_controller_hpp
#include <vector>


/*
 Nimmt Stoppuhraufgaben an
 Ruft Callbackfunktion bei Ablauf des Timers
 */

class TimerControllerElement {
public:
    TimerControllerElement() {
        callback = 0;
        time = 0;
        parameter = 0;
    }
    
    void (*callback)(int);
    double time;
    int parameter;
};


class TimerController {
private:
    std::vector<TimerControllerElement> eventQueue;
    
public:
    void simulationtime(double time);
    
    //add timer callback
    void addController(void (*callback)(int), int _param, double timeout);
};

#endif /* timer_controller_hpp */
