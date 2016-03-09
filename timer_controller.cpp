//
//  timer_controller.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 09.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "timer_controller.hpp"



void TimerController::simulationtime(double time) {
    for (std::vector<TimerControllerElement>::iterator it = eventQueue.begin(); it != eventQueue.end(); ) {
        it->time -= time;
        if (it->time <= 0) {
            it->callback(it->parameter);
            it = eventQueue.erase(it);
        } else {
            it++;
        }
    }
}



void TimerController::addController(void (*callback)(int), int _param, double timeout) {
    TimerControllerElement tce;
    tce.callback = callback;
    tce.parameter = _param;
    tce.time = timeout;
    
    eventQueue.push_back(tce);
}