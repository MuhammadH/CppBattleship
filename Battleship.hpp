//
//  Battleship.hpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//


#ifndef Battleship_hpp
#define Battleship_hpp

// probably should have called this Ship.hpp
// oh, well

#include <stdio.h>
#include <iostream>
#include <string>



using namespace std;

class Ship {
protected:
    string type;
    int length;
    
    int intType;
    
    int xLocation;
    int yLocation;
    char orientation;
    
    bool hasBeenHit;
    int livingPieces;
    
    string shipTypes[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    int shipLengths[5] = {5, 4, 3, 3, 2};
    int intTypes[5] = {1, 2, 3, 4, 5};
public:
    Ship () {
        
    }
    
    void createShip (string newType, char newOrientation, int xloc, int yloc);
    
    bool hitThisShip ();
    bool isAlive ();
    bool isSunkCompletely ();
    
    string getType () {
        return type;
    }
    int getLenth () {
        return length;
    }
    int getXLoc () {
        return xLocation;
    }
    int getYLoc () {
        return yLocation;
    }
    char getOrientation () {
        return orientation;
    }
    int getIntType () {
        return intType;
    }
};


#endif /* Battleship_hpp */
