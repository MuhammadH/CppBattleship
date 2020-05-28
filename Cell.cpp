//
//  Cell.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include "Cell.hpp"

bool Cell::insertShip(Ship &newShip) {
    // do not insert unless the contained ship is a nullptr
    if (containedShip != nullptr) {
        return false;
    }
    
    // set ship ptr
    containedShip = &newShip;
    containsShip = true;
    
    return true;
}
