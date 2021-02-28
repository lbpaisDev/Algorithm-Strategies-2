#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 1

//=========== STRUCTURES ===========\\
//Define a single game. Each game has
//board size, max moves, sum of tile values and solution moves (no solution if sol_moves = 0).
typedef struct
{
	int boardsize;
	int sum;
	int maxmoves;
	int sol_moves;
} game;

//Print game
void printgame(game *newgame, int currboard[])
{
	printf("\n\t=====CURRENT GAME=====\n");
	printf("   Board Size: %d\t Max moves: %d\n", newgame->boardsize, newgame->maxmoves);
	for (int i = 0; i < newgame->boardsize * newgame->boardsize; i++)
	{
		printf("\t%d", currboard[i]);
		printf(" ");

		if ((i + 1) % newgame->boardsize == 0)
		{
			printf("\n");
		}
	}
	printf("\t=====END OF CURRENT GAME=====\n\n");
}

//=========== GAME MOVES ===========\\
//Receives a game
//Outputs a game with a swipe up
void swipeup(int board[], int boardsize)
{
	int repeat = 0;
	int hasmerged[boardsize * boardsize];
	memset(hasmerged, 0, sizeof(int) * boardsize * boardsize);

	for (int i = boardsize; i < boardsize * boardsize; i++)
	{
		if (board[i] != 0)
		{
			if (board[i - boardsize] == 0)
			{
				repeat = i - boardsize * 2;
				while (repeat > -1 && board[repeat] == 0)
				{
					repeat -= boardsize;
				}

				board[repeat + boardsize] += board[i];
				board[i] = 0;

				if (board[repeat + boardsize] == board[repeat] && hasmerged[repeat] == 0)
				{

					board[repeat] += board[repeat + boardsize];
					board[repeat + boardsize] = 0;
					hasmerged[repeat] += 1;
				}
			}
			else if (board[i - boardsize] == board[i] && hasmerged[i - boardsize] == 0)
			{
				board[i - boardsize] += board[i];
				board[i] = 0;
				hasmerged[i - boardsize] = 1;
			}
		}
	}
}

//Receives a game
//Outputs a game with a swipe down
void swipedown(int board[], int boardsize)
{
	int repeat = 0;
	int hasmerged[boardsize * boardsize];
	memset(hasmerged, 0, sizeof(int) * boardsize * boardsize);

	for (int i = boardsize * boardsize - boardsize - 1; i > -1; i--)
	{
		if (board[i] != 0)
		{
			if (board[i + boardsize] == 0)
			{
				repeat = i + boardsize * 2;
				while (repeat < boardsize * boardsize && board[repeat] == 0)
				{
					repeat += boardsize;
				}
				board[repeat - boardsize] += board[i];
				board[i] = 0;

				if (board[repeat - boardsize] == board[repeat] && hasmerged[repeat] == 0)
				{
					board[repeat] += board[repeat - boardsize];
					board[repeat - boardsize] = 0;
					hasmerged[repeat] += 1;
				}
			}
			else if (board[i + boardsize] == board[i] && hasmerged[i + boardsize] == 0)
			{
				board[i + boardsize] += board[i];
				board[i] = 0;
				hasmerged[i + boardsize] = 1;
			}
		}
	}
}

//Receives a game
//Outputs a game with a swipe left
void swipeleft(int board[], int boardsize)
{
	int repeat;
	int hasmerged[boardsize * boardsize];
	memset(hasmerged, 0, sizeof(int) * boardsize * boardsize);

	for (int i = 1; i < boardsize * boardsize; i++)
	{
		if (i % boardsize == 0)
		{
			i++;
		}

		if (board[i] != 0)
		{
			if (board[i - 1] == 0)
			{
				repeat = i - 2;
				while (repeat % boardsize != boardsize - 1 && board[repeat] == 0)
				{
					repeat -= 1;
				}
				board[repeat + 1] += board[i];
				board[i] = 0;

				if (board[repeat + 1] == board[repeat] && hasmerged[repeat] == 0)
				{

					board[repeat] += board[repeat + 1];
					board[repeat + 1] = 0;
					hasmerged[repeat] += 1;
				}
			}

			else if (board[i - 1] == board[i] && hasmerged[i - 1] == 0)
			{
				board[i - 1] += board[i];
				board[i] = 0;
				hasmerged[i - 1] = 1;
			}
		}
	}
}

//Receives a game
//Outputs a game with a swipe right
void swiperight(int board[], int boardsize)
{
	int repeat = 0;
	int hasmerged[boardsize * boardsize];
	memset(hasmerged, 0, sizeof(int) * boardsize * boardsize);

	for (int i = boardsize - 2; i < boardsize * boardsize - 1; i--)
	{
		if (i % boardsize == boardsize - 1 || i < 0)
		{
			i += boardsize * 2 - 1;
		}

		if (board[i] != 0)
		{
			if (board[i + 1] == 0)
			{
				repeat = i + 2;
				while (repeat % boardsize != 0 && board[repeat] == 0)
				{
					repeat += 1;
				}
				board[repeat - 1] += board[i];
				board[i] -= board[i];

				if (board[repeat - 1] == board[repeat] && hasmerged[repeat] == 0)
				{

					board[repeat] += board[repeat - 1];
					board[repeat - 1] = 0;
					hasmerged[repeat] += 1;
				}
			}
			else if (board[i + 1] == board[i] && hasmerged[i - 1] == 0)
			{
				board[i + 1] += board[i];
				board[i] -= board[i];
				hasmerged[i + 1] = 1;
			}
		}
	}
}

int check_sol(int board[], int boardsize, int sum)
{
	for (int i = 0; i < boardsize * boardsize; i++)
	{
		if (board[i] == sum)
		{
			return 1;
		}
	}
	return 0;
}

void copy_currboard(int newboard[], int board[], int boardsize)
{
	for (int i = 0; i < boardsize * boardsize; i++)
	{
		newboard[i] = board[i];
	}
}

//=========== SOLVEGAME ===========\\
//Function that actually solves the game
//similar to the square problem from class
//limit recursion using M (max number of moves) and previously
//found solutions to speedup the process
void solvegame(game *newgame, int board[], int swipe, int depth)
{
	if (DEBUG)
	{
		printgame(newgame, board);

		int gameloop = 1;
		int command;

		while (gameloop)
		{
			scanf("%d", &command);
			switch (command)
			{
			case 8:
				swipeup(board, newgame->boardsize);
				break;
			case 2:
				swipedown(board, newgame->boardsize);
				break;
			case 4:
				swipeleft(board, newgame->boardsize);
				break;
			case 6:
				swiperight(board, newgame->boardsize);
				break;
			default:
				gameloop = 0;
				break;
			}
			printgame(newgame, board);
		}
	}
	/*
	if ((newgame->sol_moves > 0 && depth == newgame->maxmoves) || depth > newgame->maxmoves)
	{
		return;
	}

	int currboard[newgame->boardsize * newgame->boardsize];
	copy_currboard(currboard, board, newgame->boardsize);

	switch (swipe)
	{
	case 1:
		swipeup(currboard, newgame->boardsize);
		break;
	case 2:
		swiperight(currboard, newgame->boardsize);
		break;
	case 3:
		swipedown(currboard, newgame->boardsize);
		break;
	case 4:
		swipeleft(currboard, newgame->boardsize);
		break;
	default:
		break;
	}

	if (check_sol(currboard, newgame->boardsize, newgame->sum) == 1)
	{
		newgame->sol_moves = depth;
		return;
	}

	solvegame(newgame, currboard, 1, depth + 1);
	solvegame(newgame, currboard, 2, depth + 1);
	solvegame(newgame, currboard, 3, depth + 1);
	solvegame(newgame, currboard, 4, depth + 1);
*/
}

//=========== GETINPUT ===========\\
//Function that reads the input from stdin and calls solve game for each board
void getInput()
{
	//Local variables
	int ntests;
	game *newgame;

	newgame = (game *)malloc(sizeof(game));

	//Get number of tests in a file
	scanf("%d", &ntests);

	for (int i = 0; i < ntests; i++)
	{
		//For each new game get boardsize, maxmoves and board
		//Allocate space for game board
		scanf("%d %d", &newgame->boardsize, &newgame->maxmoves);
		newgame->sum = 0;
		newgame->sol_moves = 0;

		int board[newgame->boardsize * newgame->boardsize];

		//Parse each new line into its columns and store respective values
		for (int j = 0; j < newgame->boardsize * newgame->boardsize; j++)
		{
			//Each token is a number in the board
			//If board is 0 slot is empty
			scanf("%d", &board[j]);

			// sum to check if solution was achieved
			newgame->sum += board[j];
		}

		//Solve board
		solvegame(newgame, board, 0, 0);

		//Print solution accordinglly
		if (newgame->sol_moves == 0)
		{
			printf("no solution\n");
		}
		else
		{
			printf("%d\n", newgame->sol_moves);
		}
	}
}

int main()
{
	getInput();
	return 0;
}