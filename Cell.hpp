//
//  Cell.hpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include <string>

#include "Battleship.hpp"

using namespace std;

class Cell {
    bool containsShip;
    Ship* containedShip;
    bool hasBeenHitByEnemy;
    
public:
    Cell () {
        containsShip = false;
        containedShip = nullptr;
        hasBeenHitByEnemy = false;
    }
    
    bool getContainsShip () {
        return containsShip;
    }
    Ship* getContainedShip () {
        return containedShip;
    }
    bool getHasBeenHitByEnemy () {
        return hasBeenHitByEnemy;
    }
    
    void hit () {
        hasBeenHitByEnemy = true;
    }
    
    bool insertShip (Ship& newShip);
};

#endif /* Cell_hpp */
