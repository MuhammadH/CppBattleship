//
//  Grid.hpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>

#include "Cell.hpp"


using namespace std;

class Grid {
    Cell playField[10][10];
    int ownedByPlayer; // player 1 is the player // player 2 is the computer
    
public:
    Grid (int playerNumber); 
    
    int getOwner () {return ownedByPlayer;}
    
    Cell& at (int x, int y);
    
    void printShipPlacement ();
    void printHitPlacement (bool oneHitMode);
};

#endif /* Grid_hpp */
