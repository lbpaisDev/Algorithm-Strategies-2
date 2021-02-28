#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0

//=========== STRUCTURES ===========\\
//Define a single game. Each game has
//board size, max moves and respective board.
typedef struct
{
	int boardsize;
	int *board;
  int sum;
	int maxmoves;
  int sol_moves;
} game;

//Print game
void printgame(game *newgame)
{
	printf("\n\t=====CURRENT GAME=====\n");
	printf("   Board Size: %d\t Max moves: %d\n", newgame->boardsize, newgame->maxmoves);
	for (int i = 0; i < newgame->boardsize * newgame->boardsize; i++)
	{
			printf("\t%d", newgame->board[i]);
			printf(" ");

      if((i+1) % newgame->boardsize == 0)
      {
		    printf("\n");
      }
	}
	printf("\t=====END OF CURRENT GAME=====\n");
}

//=========== GAME MOVES ===========\\

//Receives a game
//Outputs a game with a swipe up
void swipeup(game *currgame)
{
	int repeat;
	do
	{
		repeat = 0;
	  for (int i = currgame->boardsize; i < currgame->boardsize * currgame->boardsize; i++)
	  {
			if(currgame->board[i] != 0)
      {
        if(currgame->board[i-currgame->boardsize] == 0)
        {
          repeat = 1;
          currgame->board[i-currgame->boardsize] = currgame->board[i];
          currgame->board[i] = 0;
        }
        else if(currgame->board[i-currgame->boardsize] == currgame->board[i])
        {
          currgame->board[i-currgame->boardsize] += currgame->board[i];
          currgame->board[i] = 0;
        }
      }
	  }
	} while (repeat);
}

//Receives a game
//Outputs a game with a swipe down
void swipedown(game *currgame)
{
	int repeat;
	do
	{
		repeat = 0;
	  for (int i = currgame->boardsize * currgame->boardsize - currgame->boardsize - 1; i > -1; i--)
	  {
			if(currgame->board[i] != 0)
      {
        if(currgame->board[i+currgame->boardsize] == 0)
        {
          repeat = 1;
          currgame->board[i+currgame->boardsize] = currgame->board[i];
          currgame->board[i] = 0;
        }
        else if(currgame->board[i+currgame->boardsize] == currgame->board[i])
        {
          currgame->board[i+currgame->boardsize] += currgame->board[i];
          currgame->board[i] = 0;
        }
      }
	  }
	} while (repeat);
}

//Receives a game
//Outputs a game with a swipe left
void swipeleft(game *currgame)
{
	int repeat;
	do
	{
    repeat = 0;
	  for (int i = 1; i < currgame->boardsize * currgame->boardsize; i++)
	  {
      if(i % currgame->boardsize == 0)
      {
        i++;
      }
    
			if(currgame->board[i] != 0)
      {
        if(currgame->board[i-1] == 0)
        {
          repeat = 1;
          currgame->board[i-1] = currgame->board[i];
          currgame->board[i] = 0;
        }
        else if(currgame->board[i-1] == currgame->board[i])
        {
          currgame->board[i-1] += currgame->board[i];
          currgame->board[i] = 0;
        }
      }
	  }
	} while (repeat);
}

//Receives a game
//Outputs a game with a swipe right
void swiperight(game *currgame)
{
	int repeat = 0;
	do
	{
    repeat = 0;
	  for (int i = currgame->boardsize - 2; i < currgame->boardsize * currgame->boardsize - 1; i--)
	  {
      if(i % currgame->boardsize == 0)
      {
        i += currgame->boardsize * 2 - 2;
      }
    
			if(currgame->board[i] != 0)
      {
        if(currgame->board[i+1] == 0)
        {
          repeat = 1;
          currgame->board[i+1] = currgame->board[i];
          currgame->board[i] = 0;
        }
        else if(currgame->board[i+1] == currgame->board[i])
        {
          currgame->board[i-1] += currgame->board[i];
          currgame->board[i] = 0;
        }
      }
	  }
	} while (repeat);
}

int check_sol(game *currgame)
{
  for(int i = 0; i < currgame->boardsize * currgame->boardsize; i++)
  {
    if(currgame->board[i] == currgame->sum)
    {
      return 1;
    }
  }

  return 0;
}

//=========== SOLVEGAME ===========\\
//Function that actually solves the game
//similar to the square problem from class
//limit recursion using M (max number of moves) and previously
//found solutions to speedup the process
void solvegame(game *currgame, int swipe, int depth)
{
  if((currgame->sol_moves > 0 && depth == currgame->maxmoves) || depth > currgame->maxmoves)
  {
    return;
  }
  
  switch(swipe)
  {
    case 1:
      swipeup(currgame);
      break;
    case 2:
      swiperight(currgame);
      break;
    case 3:
      swipedown(currgame);
      break;
    case 4:
      swipeleft(currgame);
      break;
    default:
      break;
  }

  if(check_sol(currgame) == 1)
  {
    currgame->sol_moves = depth;
    return;
  }

  solvegame(currgame, 1, depth+1);
  solvegame(currgame, 2, depth+1);
  solvegame(currgame, 3, depth+1);
  solvegame(currgame, 4, depth+1);
}

//=========== GETINPUT ===========\\
//Function that reads the input from stdin and calls solve game for each board
void getInput()
{
	//Local variables
	int ntests;
	game *newgame;

	//Get number of tests in a file
	scanf("%d", &ntests);
	
  newgame = (game*) malloc(sizeof(game));

	for (int i = 0; i < ntests; i++)
	{
    //For each new game get boardsize, maxmoves and board
		//Allocate space for game board
		scanf("%d %d", &newgame->boardsize, &newgame->maxmoves);
		newgame->board = (int *) malloc(newgame->boardsize * newgame->boardsize * sizeof(int));
    newgame->sum = 0;
    newgame->sol_moves = 0;

		//Parse each new line into its columns and store respective values
		for (int j = 0; j < newgame->boardsize * newgame->boardsize; j++)
		{
		  //Each token is a number in the board
		  //If board is 0 slot is empty
      scanf("%d", &newgame->board[j]);
        
			// sum to check if solution was achieved
      newgame->sum += newgame->board[j];
		}

    printgame(newgame);
    
		//Solve board
		solvegame(newgame, 0, 0);

		//Print solution accordinglly
		if (newgame->sol_moves ==  0)
		{
			printf("no solution\n");
		}
		else
		{
			printf("%d\n", newgame->sol_moves);
		}
	  
    //Free board
    free(newgame->board);
	}

	//Free game structure 
	free(newgame);
}

int main()
{
	getInput();
	return 0;
}
