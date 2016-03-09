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

class TimerControllerElement {
public:
    void (*callback)(int) = 0;
    double time = 0;
    int parameter = 0;
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
