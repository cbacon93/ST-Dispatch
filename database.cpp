//
//  database.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#include "database.hpp"


void Database::initData() {
    sim_resetted.set(false);
    sim_running.set(false);
    
    exampleCounter.set(0);
}