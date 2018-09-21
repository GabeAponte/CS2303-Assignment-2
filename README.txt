# CS2303-Assignment-2
Gabriel Aponte, gaaponte
CS2303 PA2 README

Game of Life Rules:
The game is played on a rectangular grid of cells, so that each cell has eight neighbors (adjacent cells). Each cell is either occupied by an organism or not. 
A pattern of occupied and unoccupied cells in the grid is called a generation. The rules for deriving a new generation from the previous generation are these:–
    1. Death. If an occupied cell has 0, 1, 4, 5, 6, 7, or 8 occupied neighbors, the organism dies (0 or 1 of loneliness; 4 thru 8 of overcrowding).
    2. Survival. If an occupied cell has two or three neighbors, the organism survives to the next genera-tion.
    3. Birth. If an unoccupied cell has precisely three occupied neighbors, it becomes occupied by a new organism.
Once started with an initial configuration of organisms (Generation 0), the game continues from one generation to the next until one of three conditions is met for termination:
    1. all organisms die, or
    2. the pattern of organisms repeats itself from a previous generation, or
    3. a predefined number of generations is reached.

How to run the program:
   First, unzip the folder and compile the program with 'make'. Then enter the command './life rowsTotal columnsTotal gens inputFile [print] [pause]'. rowsTotal is the amount of rows
you want to use for the grid. columnsTotal is the amount of columns you want to used for the grid. gens is the amount of generations you want to run. inputFile is the file you want 
to use as a test case. These files are in the zipfile. Then there are the optional comands of print and pause that can be used by either typing 'y' for yes and 'n' for no. The print
comand allows the program to print out the game. The pause command allows the program to stop after each generation and wait for the user to press 'enter' to run the next generation. 
     
Test cases for you to run: 
  ./life 3 8 10 acorn.txt y y
      This test case should run through ten generations and end when the generation limit of ten is reached

  ./life 8 8 10 blinker.txt y n
       This test case will go through 3 generations and then terminate due to oscillation at that generation. 

Loop Invariants in Source Code:
Loop invariant 1: The for loop will run when the row integer is less than the total amount of rows.
Loop invariant 2: The for loop will run when the column integer is less than the total amount of columns.
Loop invariant 3: The for loop will run when the row integer is less than the total amount of rows. 
Loop invariant 4: The for loop will run when the column integer is less than the total amount of columns.
Loop invariant 5: The for loop will run when the row integer is less than the total amount of rows.
Loop invariant 6: The for loop will run when the column integer is less than the total amount of columns.
Loop invariant 7: The for loop will run when the row integer is less than the total amount of rows.
Loop invariant 8: The for loop will run when the column integer is less than the total amount of columns.
Loop invariant 10: The for loop will run when the interger gen is less than total amount of gens. 
Loop invariant 10: The while loop will run when there is another line of the inputed file to read.
Loop invariant 11: the while loop will run when there is another line of the file to read. 
Loop invariant 12: The for loop will run when there is another character in lextLine.
Loop invariant 13: The for loop will run when the row integer is less than the total amount of rows.
Loop invariant 14: The for loop will run when the column integer is less than the total amount of columns.
