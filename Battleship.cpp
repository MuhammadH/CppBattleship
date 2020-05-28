//
//  Battleship.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include "Battleship.hpp"

using namespace std;

void Ship::createShip (string newType, char newOrientation, int xloc, int yloc) {
    // populate this ship's data based on inputs
    type = newType;
    for (int i = 0; i < 5; i++) {
        if (newType == shipTypes[i]) {
            length = shipLengths[i];
            livingPieces = shipLengths[i];
            intType = intTypes[i];
        }
    }
    orientation = newOrientation;
    xLocation = xloc;
    yLocation = yloc;
    hasBeenHit = false;
}

bool Ship::hitThisShip() {
    // if this ship has already been hit
    if (hasBeenHit) {
        // take away a living piece and return
        livingPieces -= 1;
        return false;
    }
    
    // else
    // change has been hit and take away a living piece
    hasBeenHit = true;
    livingPieces -= 1;
    return true;
}

bool Ship::isAlive() {
    // if has been hit, then this ship is not alive (one-hit mode)
    if (hasBeenHit) {
        return false;
    }
    return true;
}

bool Ship::isSunkCompletely() {
    // if all pieces of this ship have been hit
    // then it's entirely sunk
    if (livingPieces == 0) {
        return true;
    }
    return false;
}

