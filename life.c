/* PA2: Game of Life -- Gabe Aponte, gaaponte
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twoD.h"

/** makeBoard creates the grid with the organisms that use up cells.
 * @param  rowsTotal     the total amount of rows
 * @param  columnsTotal  the total number of columns
 * @param  board   an array of integers that shows if a cell is used by an organism in the board.
 */

void makeBoard(int rowsTotal, int columnsTotal, int **board){
    //Loop invariant 1: The for loop will run when the row integer is less than the total amount of rows.
    for(int r = 0; r < rowsTotal; r++){

        //Loop invariant 2: The for loop will run when the column integer is less than the total amount of columns.
        for(int c = 0; c < columnsTotal; c++){

            //Checks if the cell has an organism
            if(board[r][c]){
                printf("x"); //Prints x if there is an organism using the cell
            }else{
                printf(" "); //Prints o if there isn't and orhanism using the cell
            }
        }
        printf("\n");
    }
}

/** isCellUsed determines if a cell is used or not
 * @param  rowsTotal      the total amount of rows
 * @param  columnsTotal   the total amount of columns
 * @param  r      the row of the cell that you want to use
 * @param  c      the column of the cell that you want to use
 * @param  board  an array of integers that shows if a cell is used by an organism in the board.
 * @return an integer telling if the cell is in the inputed row and column.
 */

int isCellUsed(int rowsTotal, int columnsTotal, int r, int c, int **board){

    //If the inputed row is greater than or equal to the total amount of rows then the cell is unused.
    if(r >= rowsTotal){
        return 0;
    }

    //If the inputed row is less than zero then the cell is unused.
    if(r < 0){
        return 0;
    }

    //If the inputed column is greater than or equal to the total amount of columns then the cell is unused.
    if(c >= columnsTotal){
        return 0;
    }

    //If the inputed column is less than zero then the cell is unused.
    if(c < 0){
        return 0;
    }

    //If all these fail then return what is in the board array for the inputed row and column.
    return board[r][c];
}

/** countSurroundingUsedCells determines the number of cells that are used around an inputed cell.
 * @param  rowsTotal      the total amount of rows
 * @param  columnsTotal   the total amount of columns
 * @param  r         the row of the cell that you want to use
 * @param  c         the column of the cell that you want to use
 * @param  board     an array of integers that shows if a cell is used by an organism.
 * @return an integer telling the total amount of used cells surrounding the inputed cell.
 */

int countSurroundingUsedCells(int rowsTotal, int columnsTotal, int r, int c, int **board){
    int numUsedCells = 0; //stores the amount of used cells that are surrounding the inputed cell

    //Top cells, adds to numUsedCell for every used cell that is direclty above, above to the right and above to the left of the current cell.
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r-1, c-1, board);
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r, c-1, board);
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r+1, c-1, board);

    //Bottom cells, adds to numUsedCell for every used cell that is directly below, below to the left and below to the right of the current cell
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r-1, c+1, board);
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r, c+1, board);
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r+1, c+1, board);

    //Neighboring Cells, adds to numUsedCell for every used cell that is direclty on the left and right of the current cell.
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r-1, c, board);
    numUsedCells += isCellUsed(rowsTotal, columnsTotal, r+1, c, board);

    return numUsedCells;
}

/** playGen processes the generations in the game a checks for errors
 * @param  rowsTotal      the total amount of rows
 * @param  columnsTotal   the total amount of columns
 * @param  gen            integer telling what generation is being used
 * @param  print          an integer telling the program to print out the grid or not.
 * @param  oldGen         points to generations that were already used
 * @param  newGen         points to the next generation to come
 * @param  checkOscillation  points to whether or not the generations oscillate
 * @return an integer representing if any erros occured. 1 being there were errors and 0 being there were none
 */

int playGen(int rowsTotal, int columnsTotal, int gen, int doPrint, int **oldGen, int **newGen, int **checkOscillation){

    //Loop invariant 3: The for loop will run when the row integer is less than the total amount of rows.
    for(int r = 0; r < rowsTotal; r++){

        //Loop invariant 4: The for loop will run when the column integer is less than the total amount of columns.
        for(int c = 0; c < columnsTotal; c++){

            int surroundingCells = countSurroundingUsedCells(rowsTotal, columnsTotal, r, c, oldGen); //Stores the number of surrounding organisms in used cells.

            //Checks if the organism dies when the number of surrounding cells is less than two and the cell is used.
            if(surroundingCells < 2 && oldGen[r][c] == 1){
                newGen[r][c] = 0;//Organism dies
            }

            //Checks if the organism dies when the number of surrounding cells is greater than 3 and the cell is used.
            if(surroundingCells > 3 && oldGen[r][c] == 1){
                newGen[r][c] = 0;//Organism dies
            }

            //Checks if the organism lives when the number of surrounding cells is greater than 2 and less than four and the cell is used.
            if(surroundingCells >= 2 && surroundingCells < 4 && oldGen[r][c] == 1){
                newGen[r][c] = 1;//Organism lives
            }

            //Checks if the organism lives when the number of surrounding cells is equal to 3 the cell is used.
            if(surroundingCells == 3 && oldGen[r][c] == 0){
                newGen[r][c] = 1;//Organism lives
            }
        }
    }

    int oscillates = 1; //Stores if the generations oscillate.
    int repeats = 1; //Stores if generations repeats.

    //Loop invariant 5: The for loop will run when the row integer is less than the total amount of rows.
    for(int r = 0; r < rowsTotal; r++){

        //Loop invariant 6: The for loop will run when the column integer is less than the total amount of columns.
        for(int c = 0; c < columnsTotal; c++){

            //Checks if the new generation does not print the same pattern as last generation.
            if(oldGen[r][c] != newGen[r][c]){
                repeats = 0;//Sets repeats to false and there is no error
            }

            //Checks if the new generation does not print the same pattern as two generations back
            if(newGen[r][c] != checkOscillation[r][c]){
                oscillates = 0;//Sets oscillates to false and there is no error
            }
        }
    }

    //Checks if user wants to print the board
    if(doPrint){
        makeBoard(rowsTotal, columnsTotal, newGen);//prints the board
    }

    //Checks if repeats is true and it is not on the first generation.
    if(repeats == 1 && gen != 0){
        printf("Game ended due to repetition at generation [%d] \n", gen);//prints this error message and returns 1.
        return 1;
    }

    //Checks if oscillates is true and it is not on the first generation.
    if(oscillates == 1 && gen != 0 && gen != 1){
        printf("Game ended due to oscillation at generation [%d] \n", gen);//prints this error message and returns 1.
        return 1;
    }

    return 0;//returns 0 if there are no errors.
}

/** life  runs the Game of Life
 * @param  rowsTotal     the total amount of rows
 * @param  columnsTotal  the total amount of columns
 * @param  gensTotal     the total amount of generations
 * @param  print         an integer telling the program to print out the grid or not.
 * @param  pause         an integer telling the program to pause before printing the next generation.
 * @param  fileGrid      the grid read from the inputed file.
 */

void life(int rowsTotal, int columnsTotal, int gensTotal, int doPrint, int doPause, int **fileGrid){
    int **G1 = make2Dint(rowsTotal, columnsTotal); //Stores the first grid
    int **G2 = make2Dint(rowsTotal, columnsTotal); //Stores the second grid
    int **G3 = make2Dint(rowsTotal, columnsTotal); //Stores the thrid grid


    //Loop invariant 7: The for loop will run when the row integer is less than the total amount of rows.
    for(int r = 0; r < rowsTotal; r++){

        //Loop invariant 8: The for loop will run when the column integer is less than the total amount of columns.
        for(int c = 0; c < columnsTotal; c++){
            G1[r][c] = fileGrid[r][c];//Sets the first grid to that of the grid from the inputed file
        }
    }

    int arraysToUseIndex = 1; //Store what grid to use for the old and new arrays to come.
    int errorOccured = 0; //Store whether playGen encountered an error

    //Loop invariant 10: The for loop will run when the interger gen is less than total amount of gens.
    for(int gen=0; gen < gensTotal; gen++){

        int ***oldArray = &G1; //Stores the old array in playGen
        int ***newArray = &G2; //Stores the new array in playGen
        int ***checkOscillation = &G3; //Checks for oscillation in playGen

        //Checks if user wants the program to print
        if(doPrint){
            printf("\nGeneration %d\n", gen); //Prints out a label for generation
        }

        if(gen > 0){
            //Sees if it should use G1 & G3 for every third run.
            if(arraysToUseIndex == 3){
                oldArray = &G3;
                newArray = &G1;
                checkOscillation = &G2;
            }

            //Sees if it should use G2 & G3 for every second run.
            else if(arraysToUseIndex == 2){
                oldArray = &G2;
                newArray = &G3;
                checkOscillation = &G1;
            }

            //Sees is it should use G1 & G2 for every first run.
            else{
                oldArray = &G1;
                newArray = &G2;
                checkOscillation = &G3;
            }

            //Checks if playGen encountered an error
            if(playGen(rowsTotal, columnsTotal, gen, doPrint, *oldArray, *newArray, *checkOscillation) == 1){
                errorOccured = 1;//Sets errorOccured to trueand breaks out of the loop
                printf("\nFinal Generation:\n");
                makeBoard(rowsTotal, columnsTotal, *newArray);
                break;
            }

            if(gen == gensTotal){
                printf("\nFinal Generation:\n");
                makeBoard(rowsTotal, columnsTotal, *newArray);
            }

            //Checks if program is at the third run with G1 & G3.
            if(arraysToUseIndex == 3){
                arraysToUseIndex = 1;//Sets arraysToUseIndex back to G1 & G2

            }else{
                arraysToUseIndex++;//Uses the next one if everything else fails
            }

        }else{
            makeBoard(rowsTotal, columnsTotal, fileGrid);
        }

        //Checks if user enabled pausing.
        if(doPause){
            getchar();//Gets a new character before moving on
        }
    }

    //Checks if there were any erros throughout the loop.
    if(errorOccured != 1){
        printf("Game ended after reaching the limit of %d rounds.", gensTotal);//Displays the final message with no errors.
    }
}

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 */

int main(int argc, char **argv) {
    printf("Game of Life\n");

    char *inputFileName; // Name of file containing initial grid
    FILE *input; // Stream descriptor for file containing initial grid
    int rowsTotal = 3; // Number of rowsTotal in the grid
    int columnsTotal = 8; // Number of columnsTotal in the grid
    int gens = 10; // Number of gens to produce
    int doPrint = 0; // 1 if user wants to print each gen, 0 if not
    int doPause = 0; // 1 if user wants to pause after each gen, 0 if not
    //char **gridA; // A 2D array to hold the pattern

    // See if there are the right number of arguments on the command line
    if ((argc < 5) || (argc > 7)) {
        // If not, tell the user what to enter.
        printf("Usage:\n");
        printf("  ./life rowsTotal columnsTotal gens inputFile [print] [pause]\n");
        return EXIT_FAILURE;
    }

    rowsTotal = atoi(argv[1]); // Convert from character string to integer.
    columnsTotal = atoi(argv[2]);
    gens = atoi(argv[3]);
    inputFileName = argv[4];
    input = fopen(inputFileName, "r");

    //Checks if we can enable printing
    if(argc >= 6 && argv[5][0] == 'y'){
        doPrint = 1;//Sets doPrint to true.
    }

    //Checks if we can enable pausing
    if(argc == 7 && argv[6][0] == 'y'){
        doPause = 1;//Sets doPause to true
    }

    int errorOccured = 0; //Stores if there's any error in the given configuration.

    //Checks if the total amount of generations is negative
    if(gens < 0){
        printf("Invalid number of generations: %d\n", gens);//Prints out this error message and sets errorOccured to true
        errorOccured = 1;
    }

    //Checks if the total amount of columns is negative
    if(columnsTotal < 0){
        printf("Invalid number of columns: %d\n", columnsTotal);//Prints out this error message and sets errorOccured to true
        errorOccured = 1;
    }
    //Checks if the total amount of rows is negative
    if(rowsTotal < 0){
        printf("Invalid number of rows: %d\n", rowsTotal);//Prints out this error message and sets errorOccured to true
        errorOccured = 1;
    }

    //Checks if there is a file to read
    if (!input) {
        printf("Unable to open input file: %s\n", inputFileName);//Prints out this error message and sets errorOccured to true
    }

    //Checks an error occured to exit program with a failure
    if(errorOccured){
        return EXIT_FAILURE;
    }

    int firstRow = 0; //Stores the begining row from the file the user inputed
    int firstColumn = 0; //Stores the begining column from the file the user inputed
    int rowCount = 0; //Stores the total amount of rows from the file the user inputed
    int columnCount = 0; //Stores the total amount of columns from the file the user inputed
    char *currentLine = malloc(1000); //Allocates memory in order to read the current line of the file.

    //Loop invariant 10: The while loop will run when there is another line of the inputed file to read.
    while(fgets(currentLine, 90000, input) != NULL) {
        if(strlen(currentLine)-1 == 0){
            continue;
        }
        if(strlen(currentLine)-1 > columnCount){
            columnCount = strlen(currentLine)-1;
        }
        rowCount++;
    }

    rewind(input);//rewinds the inputed file so that it can access the lines again.

    int **fileGrid = make2Dint(rowCount, columnCount); //makes a 2D integer array for the grid in the file.
    char *nextLine = malloc(1000); //Allocates memory in order to read the current line of the file.
    int lineNum = 0; //Stores the current line number of the file

    //Loop invariant 11: the while loop will run when there is another line of the file to read.
    while(fgets(nextLine, 90000, input) != NULL) {

        //Loop invariant 12: The for loop will run when there is another character in lextLine.
        for(int i=0; i < strlen(nextLine)+1; i++){

            //Checks if the character is x
            if(nextLine[i] == 'x'){
                fileGrid[lineNum][i] = 1;//Sets the fileGrid for this position to 1, meaning there is an organism there.
            }else{
                fileGrid[lineNum][i] = 0;//Sets the file grid for this position to 0, meaing there is no orhanism there.
            }
        }
        lineNum++;
    }

    firstColumn = (columnsTotal/2)-(columnCount/2); //Sets the start of the fileGrid to the total columns divided by 2 and subtracted by half the size of the actual fileGrid column amount
    firstRow = (rowsTotal/2)-(rowCount/2); //Sets the start of the fileGrid to the total rows divided by 2 and subtracted by half the size of the actual filemap row amount
    int **parse = make2Dint(rowsTotal, columnsTotal); //Make a 2D integer array for parsing

    //Loop invariant 13: The for loop will run when the row integer is less than the total amount of rows
    for(int r=0; r < rowsTotal; r++){

        //Loop invariant 14: The for loop will run when the column integer is less than the total amount of columns
        for(int c=0; c < columnsTotal; c++){

            //Checks if program is in the fileGrid and can start to use data from it
            if(r > firstRow-1 && c > firstColumn-1 && r <= firstRow+rowCount-1 && c <= firstColumn+columnCount-1){
                parse[r][c] = fileGrid[r-firstRow][c-firstColumn];//Accesses data from the filemap.
            }else{
                parse[r][c] = 0;//Sets to 0 because the program isn't in the fileGrid.
            }
        }
    }

    life(rowsTotal, columnsTotal, gens, doPrint, doPause, parse);

    /*Once opened, you can read from the file one character at a time with fgetc().
     * You can read one line at a time using fgets().
     * You can read from standard input (the keyboard) with getchar(). */

    return EXIT_SUCCESS; //Exits program after successful run through.
}
