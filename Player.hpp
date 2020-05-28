//
//  Player.hpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/24/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <vector>
#include "Battleship.hpp"

class Player {
protected:
    int playerNumber;
    vector<Ship*> playersShips;
public:
    ~Player ();
    int determineLoss (bool oneHitSinkMode);
    vector<Ship*>& getShips () {
        return playersShips;
    }
};

// Human and Computer will be child classes of Player

class HumanPlayer : public Player {
public:
    HumanPlayer () {
        playerNumber = 1;
    }
};

class ComputerPlayer : public Player {
    /* when the game IS NOT on one-hit-sink mode, the computer
       acts semi-intelligently
       that's what this list of next hits is for
     */
    vector<int> nextHits;
public:
    vector<int>& getNextHits () {
        return nextHits;
    }
    ComputerPlayer () {
        playerNumber = 2;
    }
};

#endif /* Player_hpp */
