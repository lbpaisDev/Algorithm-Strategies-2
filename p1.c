#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0

//=========== STRUCTURES ===========\\
//Define a single game. Each game has
//board size, max moves and respective board.
typedef struct
{
	int **board;
	int boardsize;
  int sum;
	int maxmoves;
  int sol_moves;
} game;

//Print game
void printgame(game *newgame)
{
	printf("\n\t=====CURRENT GAME=====\n");
	printf("   Board Size: %d\t Max moves: %d\n", newgame->boardsize, newgame->maxmoves);
	for (int i = 0; i < newgame->boardsize; i++)
	{
		for (int j = 0; j < newgame->boardsize; j++)
		{
			printf("\t%d", newgame->board[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\t=====END OF CURRENT GAME=====\n");
}

//=========== GAME MOVES ===========\\


//Receives a game
//Outputs a game with a swipe up
void swipeup(game *currgame)
{
	int repeat = 0;
	do
	{
		repeat = 0;

	  for (int i = 1; i < currgame->boardsize; i++)
	  {
			for (int j = 0; j < currgame->boardsize; j++)
			{
				if (currgame->board[i][j] != 0)
				{
					if (currgame->board[i - 1][j] == 0)
					{
						repeat = 1;
						currgame->board[i - 1][j] = currgame->board[i][j];
						currgame->board[i][j] = 0;
					}
					else
					{
						if (currgame->board[i - 1][j] == currgame->board[i][j])
						{
							currgame->board[i - 1][j] = currgame->board[i - 1][j] + currgame->board[i][j];
							currgame->board[i][j] = 0;
						}
					}
				}
			}
	  }
	} while (repeat);
  return currgame;
}

//Receives a game
//Outputs a game with a swipe down
void swipedown(game *currgame)
{
	int repeat = 0;
	do
	{
		repeat = 0;
	  for (int i = 1; i < currgame->boardsize - 1; i++)
	  {
			for (int j = 0; j < currgame->boardsize; j++)
			{
				if (currgame->board[i][j] != 0)
				{
					if (currgame->board[i + 1][j] == 0)
					{
						repeat = 1;
						currgame->board[i + 1][j] = currgame->board[i][j];
						currgame->board[i][j] = 0;
					}
					else
					{
						if (currgame->board[i + 1][j] == currgame->board[i][j])
						{
							currgame->board[i + 1][j] = currgame->board[i + 1][j] + currgame->board[i][j];
							currgame->board[i][j] = 0;
						}
					}
				}
			}
	  }
  } while (repeat);
  return currgame;
}

//Receives a game
//Outputs a game with a swipe left
void swipeleft(game *currgame)
{
	int repeat = 0;
	for (int i = 0; i < currgame->boardsize; i++)
	{
		do
		{
			repeat = 0;

			for (int j = 1; j < currgame->boardsize; j++)
			{
				if (currgame->board[i][j] != 0)
				{
					if (currgame->board[i][j - 1] == 0)
					{
						repeat = 1;
						currgame->board[i][j - 1] = currgame->board[i][j];
						currgame->board[i][j] = 0;
					}
					else
					{
						if (currgame->board[i][j - 1] == currgame->board[i][j])
						{
							currgame->board[i][j - 1] = currgame->board[i][j - 1] + currgame->board[i][j];
							currgame->board[i][j] = 0;
						}
					}
				}
			}
		} while (repeat);
	}
  return currgame;
}

//Receives a game
//Outputs a game with a swipe right
void swiperight(game *currgame)
{
	int repeat = 0;
	for (int i = 0; i < currgame->boardsize; i++)
	{
		do
		{
			repeat = 0;

			for (int j = 0; j < currgame->boardsize - 1; j++)
			{
				if (currgame->board[i][j] != 0)
				{
					if (currgame->board[i][j + 1] == 0)
					{
						repeat = 1;
						currgame->board[i][j + 1] = currgame->board[i][j];
						currgame->board[i][j] = 0;
					}
					else
					{
						if (currgame->board[i][j + 1] == currgame->board[i][j])
						{
							currgame->board[i][j + 1] = currgame->board[i][j + 1] + currgame->board[i][j];
							currgame->board[i][j] = 0;
						}
					}
				}
			}
		} while (repeat);
	}
  return currgame;
}

int check_sol(game *currgame)
{
  for(int i = 0; i < currgame->boardsize; i++)
  {
    for(int j = 0; j < currgame->boardsize; j++)
    {
      if(currgame->board[i][j] == currgame->sum)
      {
        return 1;
      }
    }
  }

  return 0;
}

//=========== SOLVEGAME ===========\\
//Function that actually solves the game
//TO-DO - should explore recursion
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
	int ntests, tile_val, sum;
	char *token, *line;
	game *newgame;

	//Get number of tests in a file
	scanf("%d", &ntests);
	for (int i = 0; i < ntests; i++)
	{
		//Allocate space for new game struct
		newgame = (game *)malloc(sizeof(game));

		//For each new game get boardsize, maxmoves and board
		//Ignore newline so its picked up by next fgets
		scanf("%d %d *[^\n]", &newgame->boardsize, &newgame->maxmoves);

		//Allocate for destination char of fgets
		line = calloc(newgame->boardsize * 2 + 1, sizeof(char));

		//Allocate space for game board
		newgame->board = (int **)malloc(newgame->boardsize * sizeof(int *));
		for (int l = 0; l < newgame->boardsize; l++)
			newgame->board[l] = (int *)malloc(newgame->boardsize * sizeof(int));

    sum = 0;

		//Parse each new line into its columns and store respective values
		for (int j = 0; j < newgame->boardsize; j++)
		{
			//Get line
			fgets(line, sizeof(char) * (newgame->boardsize * 2 + 1), stdin);
			//Line tokenizer
			token = strtok(line, " ");
			for (int k = 0; token != NULL; k++)
			{
        tile_val = atoi(token);

				//Each token is a number in the board
				//If board is 0 slot is empty
				newgame->board[j][k] = tile_val;
        
				// sum to check if solution was achieved
        sum += tile_val;

        //Next token
				token = strtok(NULL, " ");
			}
		}

    newgame->sum = sum;
    newgame->sol_moves = 0;

    printgame(newgame);
		//Solve board
		solvegame(newgame, 0, 0);
    printgame(newgame);
		//Print solution accordinglly
		if (newgame->sol_moves ==  0)
		{
			printf("no solution\n");
		}
		else
		{
			printf("%d\n", newgame->sol_moves);
		}
	}

	//Free all previously allocated memory
	free(line);
	free(newgame->board);
	free(newgame);
}

int main()
{
	getInput();
	return 0;
}
