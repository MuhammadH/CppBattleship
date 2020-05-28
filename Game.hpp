//
//  Game.hpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/23/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "Grid.hpp"
#include "Player.hpp"



using namespace std;

class Game {
    
    Grid* playerGrid;
    Grid* computerGrid;
    
    bool oneHitSinkMode;
    
    HumanPlayer* humanPlayer;
    ComputerPlayer* computerPlayer;
    
public:
    ~Game();
    
    void gameLoop ();
    
    void createPlayersGrid ();
    bool placeShip (Ship& thisShip, Grid& thisGrid);
    void populateComputerGrid ();
    
    int turnLoop ();
    void playerTurn ();
    void computerTurn ();
    int determineGameOver ();
    void endGame (int condition);
    
    void setOneHItSink ();
};

#endif /* Game_hpp */
