//
//  Grid.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include "Grid.hpp"
#include <iostream>

using namespace std;

Cell& Grid::at(int x, int y) {
    // check if out of range
    if (x < 0 || y < 0 || y > 9 || x > 9) {
        throw 21;
    }
    
    return playField[x][y];
}

Grid::Grid (int playerNumber) {
    // set player number
    // 1 for human // 2 for computer
    ownedByPlayer = playerNumber;
    
    // populate each spot in the set with a new cell
    for (int i  = 0; i < 10; i++) {
        
        for (int j  = 0; j < 10; j++) {
            
            Cell newCell;
            playField[i][j] = newCell;
            
        }
        
    }
}

void Grid::printShipPlacement() {
    
    // go to every spot in the grid
    for (int i = 0; i < 10; i++) {
        
        for (int j = 0; j < 10; j++) {
            if (playField[j][i].getContainsShip()) {
                // print the ship type number if there's a ship
                cout << playField[j][i].getContainedShip()->getIntType();
            } else {
                // if not, print zero
                cout << 0;
            }
        }
        // end the line after every internal for loop
        cout << endl;
    }
}

void Grid::printHitPlacement(bool oneHitMode) {
    for (int i = 0; i < 10; i++) {
        // go to every cell in the grid
        
        for (int j = 0; j < 10; j++) {
            // IMPORTANT
            // if the cell contains a ship that is no longer alive in one-hit mode
            // then print it even if that spot hasn't been hit
            if (playField[j][i].getContainsShip() && !playField[j][i].getHasBeenHitByEnemy()) {
                
                if (oneHitMode && !playField[j][i].getContainedShip()->isAlive()) {
                    cout << 'O';
                    continue;
                }
                
            }
            
            // print if this spot has been hit
            if (playField[j][i].getHasBeenHitByEnemy()) {
                
                if (playField[j][i].getContainsShip()) {
                    // print hit
                    cout << 'O';
                } else {
                    // print miss
                    cout << 'X';
                }
                
            } else {
                // print '_' if this spot has not been hit
                cout << '_';
            }
        }
        // end the line after every internal for loop
        cout << endl;
    }
}

