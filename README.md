# game-of-life-demo
This is an implementation of Conway's Game of Life in C.  

# Overview

This program is designed to take an input text file and use it to play a finite version of John
Conway's game of life. The program can be run exclusively from the command line. The game of life is played on a two dimensional grid of square cells. Each cell has one of the two possible states: live or dead. After each generation, each cell is changed according to the following rules:
- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

# Testing

This project utilizes a Makefile and was tested using GCC (GNU Compiler Collection). Navigate to the directory containing the files downloaded from github and run the following command:

`make all`

This will compile a executable called 'life.exe'. This program can be run using the following command:

`life NR NC gens input [print] [pause]`

where NR (integer) is the number of rows desired for the game board, NC (integer) is the number of 
columns desired in the game board, gens (integer) is the number of generations for which you wish to 
play the game of life, input (char) is the file contain the initial pattern for the game, 
print (optional) (y or n) decides if you want to print every generation or just the last, pause
(optional) (y or n) decides if you want to wait for the ENTER key to be pressed between generations.

The test file provided is named 'testCase.txt' and contains an example of the Gosper glider gun. 

Afterwards, the command:

`make clean` 

may be used to delete the files created with the first command.
