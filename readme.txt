
                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program plays battleship. Woo hoo! It'll read ship placements from a csv file before starting the game. 


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
This main function demonstrates plays battleship. 

Because there are a ton of files, I'm just going to combine cpp and cpp files and describe them as one entity. 


Name: Battleship
This class contains the methods and data for a ship. The ship can be made, placed, have individual pieces be hit, and be destroyed. 

Name:  Cell
Cells contain information used by the grid. A cell can be hit and it can contain a ship. 

Name:  Grid
A grid is a bunch of cells in a 10x10 square. The cells can be accessed by the grid.

Name: Player
The player holds some data relevant to each "player" (the human player and the computer). This class will mostly store a list of ships it contains. 

Name: Game
The game puts everything together and makes it work. The main function should only really access an object of the Game class. Everything else should be abstracted. 


   
*******************************************************
*  Status of program
*******************************************************

   Run make. Follow menu instructions. Have a fun. 

   The program was developed and tested on Xcode g++ on OSX version 10.14.3

