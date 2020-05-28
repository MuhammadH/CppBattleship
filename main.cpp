//
//  main.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/22/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include <iostream>
#include <string>

#include "Battleship.hpp"
#include "Cell.hpp"
#include "Grid.hpp"
#include "Game.hpp"

using namespace std;



int main(int argc, const char * argv[]) {
    
    Game testGame;
    testGame.gameLoop();
    
    return 0;
}
