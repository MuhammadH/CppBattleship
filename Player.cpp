//
//  Player.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/24/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include "Player.hpp"

int Player::determineLoss(bool oneHitSinkMode) {
    // check every ship, if they're all destroyed, then the player lost
    for (int i = 0; i < playersShips.size(); i++) {
        bool living;
        
        // living condition depends on one-hit-sink mode
        if (oneHitSinkMode) {
            living = playersShips.at(i)->isAlive();
        } else {
            living = !playersShips.at(i)->isSunkCompletely();
        }
        
        
        if (living) {
            return 0;
        }
    }
    return playerNumber;
}

Player::~Player() {
    // delete every ship
    for (int i = 0; i < playersShips.size(); i++) {
        delete playersShips[i];
    }
}
