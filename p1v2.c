#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
//=========== GETINPUT ===========\\
//Function that reads the input from stdin and calls solve game for each board
*/
void getInput()
{
    //Local variables
    int ntests, boardsize, maxmoves;
    int sum = 0;

    //Get number of tests in a file
    scanf("%d", &ntests);

    for (int i = 0; i < ntests; i++)
    {
        //For each new game get boardsize, maxmoves and board
        //Allocate space for game board
        scanf("%d %d", &boardsize, &maxmoves);

        int board[boardsize * boardsize];

        //Parse each new line into its columns and store respective values
        for (int j = 0; j < boardsize * boardsize; j++)
        {
            //Each token is a number in the board
            //If board is 0 slot is empty
            scanf("%d", &board[j]);

            // sum to check if solution was achieved
            sum += board[j];
        }

        //Solve board
        int nmoves = solvegame(board, boardsize, maxmoves, sum);

        //Print solution accordinglly
        if (nmoves < 0)
        {
            printf("no solution\n");
        }
        else
        {
            printf("%d\n", nmoves);
        }
    }
}

int main()
{
    getInput();
    return 0;
}