//
//  Game.cpp
//  HussainMHW4
//
//  Created by Muhammad Hussain on 3/23/19.
//  Copyright © 2019 Muhammad Hussain. All rights reserved.
//

#include "Game.hpp"
#include <random>
#include <time.h>

using namespace std;

void Game::gameLoop() {
    // does the player want to play one-hit-sink or the full game?
    setOneHItSink();
    
    // make the player's grid
    createPlayersGrid();
    cout << "Your completed ship placements: " << endl;
    playerGrid->printShipPlacement();
    
    // make the computer's Grid
    populateComputerGrid();
    // for testing purposes
    // cout << "Computer placements: " << endl;
    // computerGrid->printShipPlacement();
    
    // play the game
    int endCondition = turnLoop();
    // end the game
    endGame(endCondition);
}

Game::~Game() {
    // delete all pointers
    delete humanPlayer;
    delete computerPlayer;
    delete playerGrid;
    delete computerGrid;
    // just a note -
    // remember that cells should not delete the ships they contain
    // leave it to the player object to delete the ships
}

void Game::createPlayersGrid () {
    
    // ignore because we asked the player to input a char earlier
    cin.ignore();
    
    // make the player
    humanPlayer = new HumanPlayer;
    
    // try to open a file
    ifstream input;
    while (!input.is_open()) {
        cout << "Enter a file name to read from: " << endl;
        cout << "For example: ship_placement3_good.csv" << endl;
        string fileName;
        getline(cin, fileName);
        
        input.open(fileName);
    }
    
    // make the player's grid
    Grid* newGrid = new Grid(1);
    playerGrid = newGrid;
    
    // these failed inputs will be used later
    vector<string> failedInputs;
    
    // these sets will be used later to convert chars to ints
    char xSetChar[10] = {'A','B','C','D','E','F','G','H','I','J'};
    int xSetInt[10] = {1,2,3,4,5,6,7,8,9,10};
    
    // for 5 ships
    for (int i = 0; i < 5; i++) {
        cout << "Ship number: " << i << endl;
        
        // get input from csv
        // ship string
        string shipLine;
        getline(input, shipLine, ',');
        
        cout << "ship: " << shipLine << endl;
        
        // placement string
        string placementLine;
        getline(input, placementLine, ',');
        
        cout << "place: " << placementLine << endl;
        
        // orientation string
        string orientationLine;
        getline(input, orientationLine, '\n');
        
        cout << "orientation: " << orientationLine << endl;
        
        // (try to) put the battleship into the grid
        
        // if add ship is true later, that means the input was valid
        // and it should be added to the ship* vector for player
        bool addShip = true;
        Ship* newShip = new Ship;
        int newXLoc = 0;
        // get numerical value for the x position
        for (int i = 0; i < 10; i++) {
            if (xSetChar[i] == placementLine.at(0)) {
                newXLoc = xSetInt[i] - 1;
            }
        }
        // get numerical value for y position
        int newYLoc = placementLine.at(1) - '0';
        newYLoc -= 1;
        // create the new ship
        newShip->createShip(shipLine, orientationLine.at(0), newXLoc, newYLoc);
        
        try {
            // try to place the ship
            placeShip(*newShip, *newGrid);
            cout << "Placing the " << newShip->getType() << " worked!" << endl;
        } catch (int x) {
            // if failed - add it to the list of ships to add manually
            cout << "Placing the " << newShip->getType() << " didn't work. D:" << endl;
            failedInputs.push_back(newShip->getType());
            // delte this ship
            delete newShip;
            // don't add it to the vector
            addShip = false;
        }
        
        if (addShip) {
            // add completely placed ship to player ship vector
            humanPlayer->getShips().push_back(newShip);
        }
        
        // print current ship placements
        cout << "Your current ship placements: " << endl;
        playerGrid->printShipPlacement();
    }
    
    // now address ships that failed to be placed
    int failCount = (int)failedInputs.size();
    if (failCount > 0) {
        // give list of failed ships
        cout << "Some ship placements failed, so we'll have to do them manually.  " << endl;
        for (int i = 0; i < failCount; i++) {
            cout << failedInputs.at(i) << " " ;
        }
        cout << " failed" << endl;
    }
    for (int i = 0; i < failCount; i++) {
        
        bool verified = false;
        
        // while not verified, try again
        while (!verified) {
            
            // let the player see their ship placements
            cout << "Your current ship placements: " << endl;
            playerGrid->printShipPlacement();
            
            // make a new ship
            Ship* newShip = new Ship;
            
            // verified is true unless set false in catch
            verified = true;
            try {
                // get new placement values
                cout << "Enter the x location for the " << failedInputs.at(i) << endl;
                cout << "(A-J)" << endl;
                char xlocChar;
                int xloc = 0;
                cin >> xlocChar;
                
                for (int i = 0; i < 10; i++) {
                    if (xlocChar == xSetChar[i]) {
                        xloc = xSetInt[i];
                    }
                }
                
                cout << "Enter the y location for the " << failedInputs.at(i) << endl;
                cout << "1 through 10" << endl;
                int yloc;
                cin >> yloc;
                
                cout << "Enter the orientation for the " << failedInputs.at(i) << endl;
                cout << "H or V" << endl;
                char orientation;
                cin >> orientation;
                
                newShip->createShip(failedInputs.at(i), orientation, xloc - 1, yloc - 1);
                
                // try to place the ship again
                placeShip(*newShip, *newGrid);
                
            } catch (int x) {
                // this means placement did not work
                cout << "no does work - try again you doof" << endl;
                verified = false;
            }
            
            if (verified) {
                // if verified, add it to the ship vector
                humanPlayer->getShips().push_back(newShip);
            }
        }
        
        
    }
}

bool Game::placeShip(Ship& thisShip, Grid& thisGrid) {
    
    // set placement values
    int xloc = thisShip.getXLoc();
    int yloc = thisShip.getYLoc();
    char orientation = thisShip.getOrientation();
    int shipLength = thisShip.getLenth();
    
    // true count counts how many potential placement spots
    // already have ships on them
    int trueCount = 0;
    if (orientation == 'V') {
        // look for occupied spots in prospective placement
        for (int i = 0; i < shipLength; i++) {
            if (thisGrid.at(xloc, yloc + i).getContainsShip()) {
                trueCount += 1;
            }
        }
    }
    else if (orientation == 'H') {
        // look for occupied spots in prospective placement
        for (int i = 0; i < shipLength; i++) {
            if (thisGrid.at(xloc + 1, yloc).getContainsShip()) {
                trueCount += 1;
            }
        }
    }
    
    if (trueCount == 0) {
        // if true count is zero, place the ship
        if (orientation == 'V') {
            for (int i = 0; i < shipLength; i++) {
                if (thisGrid.at(xloc, yloc + i).insertShip(thisShip)) {
                    trueCount += 1;
                }
            }
        }
        else if (orientation == 'H') {
            for (int i = 0; i < shipLength; i++) {
                if (thisGrid.at(xloc + i, yloc).insertShip(thisShip)) {
                    trueCount += 1;
                }
            }
        }
        
        return true;
    } else {
        // if true count is > zero, DO NOT place the ship
        // throw fail
        throw 22;
        return false;
    }
    
    return false;
}

void Game::populateComputerGrid() {
    srand((unsigned int)time(NULL)); // the warning message is really annoying
    
    computerPlayer = new ComputerPlayer;
    
    Grid* newGrid = new Grid(2);
    computerGrid = newGrid;
    
    string shipTypes[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    
    // verified determines if we need to re-try placement
    bool verified = false;
    
    // try to place 5 ships
    for (int i = 0; i < 5; i++) {
        verified = false;
        while (!verified) {
            Ship* newShip = new Ship;
            
            verified = true;
            try {
                // try random placements
                int xloc = rand() % 10;
                int yloc = rand() % 10;
                
                // try random orientation
                char orientation;
                int randForBool = xloc = rand() % 2;
                if (randForBool == 0) {
                    orientation = 'V';
                } else {
                    orientation = 'H';
                }
                
                // create the ship
                newShip->createShip(shipTypes[i], orientation, xloc, yloc);
                
                // try to place ship
                placeShip(*newShip, *newGrid);
                
            } catch (int x) {
                // delete failed ship and try again
                delete newShip;
                verified = false;
            }
            
            if (verified) {
                // if valid, add to the list of computer's ships
                computerPlayer->getShips().push_back(newShip);
            }
        }
    }
}

int Game::determineGameOver() {
    // check for both a human and computer loss
    // return 1 if player lost
    // return 2 if human lost
    
//    int condition = 0;
//    if (determinePlayerLoss()) {
//        condition = 1;
//    }
//    if (determineComputerLoss()) {
//        condition = 2;
//    }
//    return condition;
    
    
    int condition = 0;
    condition = humanPlayer->determineLoss(oneHitSinkMode);
    condition = computerPlayer->determineLoss(oneHitSinkMode);
    return condition;
}


void Game::playerTurn() {
    // print grid of cells you've already hit ****
    
    bool validHit = false;
    char xhitChar;
    int xhit = 1;
    int yhit = 1;
    
    char xSetChar[10] = {'A','B','C','D','E','F','G','H','I','J'};
    int xSetInt[10] = {1,2,3,4,5,6,7,8,9,10};
    
    while (!validHit) {
        cout << "Pick an x position to hit" << endl;
        cout << "(A-J) or Q to quit" << endl;
        cin >> xhitChar;
        
        if (xhitChar == 'Q') {
            throw 100;
        }
        
        // turn char input into a number
        for (int i = 0; i < 10; i++) {
            if (xhitChar == xSetChar[i]) {
                xhit = xSetInt[i];
            }
        }
        
        // get y input
        cout << "Pick a y position to hit" << endl;
        cout << "(1-10)" << endl;
        cin >> yhit;
        
        // reduce both values by 1 for use in grid
        xhit -= 1;
        yhit -= 1;
        
        // check if this spot has already been hit
        if (!computerGrid->at(xhit, yhit).getHasBeenHitByEnemy()) {
            // if already hit, get a new input
            validHit = true;
        }
    }
    
    // hit this cell
    computerGrid->at(xhit, yhit).hit();
    
    // determine if this cell has a ship
    // if so, hit it
    if (computerGrid->at(xhit, yhit).getContainsShip()) {
        bool newHit = computerGrid->at(xhit, yhit).getContainedShip()->hitThisShip();
        if (newHit) {
            
            if (oneHitSinkMode) {
                cout << "You sunk the computer's " <<
                computerGrid->at(xhit, yhit).getContainedShip()->getType()
                << "!" << endl;
            } else {
                cout << "You hit the computer's ship!" << endl;
                
                if (computerGrid->at(xhit, yhit).getContainedShip()->isSunkCompletely()) {
                    cout << "You sunk the computer's " <<
                    computerGrid->at(xhit, yhit).getContainedShip()->getType()
                    << "!" << endl;
                }
            }
            
            
        } else {
            
            if (oneHitSinkMode) {
                cout << "You hit a boat that has already been sunk!" << endl;
            } else {
                cout << "You hit the computer's ship!" << endl;
                
                if (computerGrid->at(xhit, yhit).getContainedShip()->isSunkCompletely()) {
                    cout << "You sunk the computer's " <<
                    computerGrid->at(xhit, yhit).getContainedShip()->getType()
                    << "!" << endl;
                }
            }
            
        }
    } else {
        cout << "You missed!" << endl;
    }
}

void Game::computerTurn() {
    srand((unsigned int)time(NULL));
    
    bool validHit = false;
    int xhit = rand() % 10;
    int yhit = rand() % 10;
    
    // make random values
    while (!validHit) {
        if (computerPlayer->getNextHits().size() > 0) {
            yhit = computerPlayer->getNextHits().at
            (computerPlayer->getNextHits().size() - 1);
            computerPlayer->getNextHits().pop_back();
            
            xhit = computerPlayer->getNextHits().at
            (computerPlayer->getNextHits().size() - 1);
            computerPlayer->getNextHits().pop_back();
        } else {
            xhit = rand() % 10;
            yhit = rand() % 10;
        }
        
        // if the computer hasn't hit this spot yet, then this is a valid hit
        if (xhit > -1 && yhit > -1 && yhit < 10 && xhit < 10
            &&
            !playerGrid->at(xhit, yhit).getHasBeenHitByEnemy()
            ) {
            validHit = true;
        }
    }
    
    // hit this cell
    playerGrid->at(xhit, yhit).hit();
    
    // check if this cell has a ship
    if (playerGrid->at(xhit, yhit).getContainsShip()) {
        // hit the ship
        bool newHit = playerGrid->at(xhit, yhit).getContainedShip()->hitThisShip();
        if (newHit) {
            
            if (oneHitSinkMode) {
                cout << "The computer sunk your " <<
                playerGrid->at(xhit, yhit).getContainedShip()->getType()
                << "!" << endl;
            } else {
                cout << "The computer hit your " <<
                playerGrid->at(xhit, yhit).getContainedShip()->getType()
                << "!" << endl;
                
                if (playerGrid->at(xhit, yhit).getContainedShip()->isSunkCompletely()) {
                    cout << "The computer sunk your " <<
                    playerGrid->at(xhit, yhit).getContainedShip()->getType()
                    << "!" << endl;
                } else {
                    // add surrounding cells to list of cell to hit next
                    // push x first
                    // then push y
                    // (it's fine if the computer picks a cell that it's already hit)
                    // (that attempt just wont be validated and it'll be removed from)
                    // (the list of next hits)
                    // (it can also go out of bounds and be fine)
                    
                    // 1.
                    computerPlayer->getNextHits().push_back(xhit);
                    computerPlayer->getNextHits().push_back(yhit-1);
                    // 2.
                    computerPlayer->getNextHits().push_back(xhit+1);
                    computerPlayer->getNextHits().push_back(yhit-1);
                    // 3.
                    computerPlayer->getNextHits().push_back(xhit+1);
                    computerPlayer->getNextHits().push_back(yhit);
                    // 4.
                    computerPlayer->getNextHits().push_back(xhit+1);
                    computerPlayer->getNextHits().push_back(yhit+1);
                    // 5.
                    computerPlayer->getNextHits().push_back(xhit);
                    computerPlayer->getNextHits().push_back(yhit+1);
                    // 6.
                    computerPlayer->getNextHits().push_back(xhit-1);
                    computerPlayer->getNextHits().push_back(yhit+1);
                    // 7.
                    computerPlayer->getNextHits().push_back(xhit-1);
                    computerPlayer->getNextHits().push_back(yhit);
                    // 8.
                    computerPlayer->getNextHits().push_back(xhit-1);
                    computerPlayer->getNextHits().push_back(yhit-1);
                }
            }
            
        } else {
            
            if (oneHitSinkMode) {
                cout << "The computer hit a boat that has already been sunk!" << endl;
            } else {
                cout << "The computer hit your " <<
                playerGrid->at(xhit, yhit).getContainedShip()->getType()
                << "!" << endl;
                
                if (playerGrid->at(xhit, yhit).getContainedShip()->isSunkCompletely()) {
                    cout << "The computer sunk your " <<
                    playerGrid->at(xhit, yhit).getContainedShip()->getType()
                    << "!" << endl;
                }
            }
            
        }
    } else {
        cout << "Computer missed!" << endl;
    }
}


int Game::turnLoop() {
    int gameOver = 0;
    
    // one turn at a time as long as gameOver == 0
    while (gameOver == 0) {
        // print cells hit on the computer's grid
        cout << "Here are the spots you've hit so far" << endl;
        cout << "O is a hit" << endl;
        cout << "X is a miss" << endl;
        computerGrid->printHitPlacement(oneHitSinkMode);
        
        if (gameOver == 0) {
            try {
                playerTurn();
            } catch (int x) {
                if (x == 100) {
                    return 3;
                }
            }
            // check for game over
            gameOver = determineGameOver();
        }
        
        if (gameOver == 0) {
            computerTurn();
            // check for game over
            gameOver = determineGameOver();
        }
    }
    
    return gameOver;
}


void Game::endGame(int condition) {
    // end the game based on condition
    if (condition == 1) {
        cout << "You lost! Hahahahahaha" << endl;
    }
    else if (condition == 2) {
        cout << "You won! Good job!" << endl;
    }
    else if (condition == 3) {
        cout << "At least you tried!" << endl;
        cout << "Your hit board:" << endl;
        computerGrid->printHitPlacement(oneHitSinkMode);
        cout << "The computer's placements:" << endl;
        computerGrid->printShipPlacement();
    }
}

void Game::setOneHItSink() {
    // see if the player wants one-hit-sink mode
    cout << "Hi! Do you want to play one-hit sink mode?" << endl;
    cout << "This means ships will sink if a player hits them just once." << endl;
    
    // this char will be used to get the player's choice
    char choice = 'U';
    
    // try to get a Y or N
    while (choice != 'N' && choice != 'Y') {
        try {
            cout << "Please enter Y or N" << endl;
            cin >> choice;
        } catch (int x) {
            
        }
    }
    
    // if yes (Y), set one hit sink to true
    if (choice == 'Y') {
        oneHitSinkMode = true;
    } else {
        oneHitSinkMode = false;
    }
}


