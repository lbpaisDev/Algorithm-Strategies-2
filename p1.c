#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int board_size = 0;
int board_values_sum = 0;
int max_moves = 0;
int sol_moves = -1;

//Print game
void print_game(int curr_board[])
{
	printf("\n\t=====CURRENT GAME=====\n");
	printf("   Board Size: %d\t Max moves: %d\n", board_size, max_moves);
	for (int i = 0; i < board_size * board_size; i++)
  {	
		printf("\t%d", curr_board[i]);
		printf(" ");

		if ((i + 1) % board_size == 0)
		{
			printf("\n");
		}
	}
	printf("\t=====END OF CURRENT GAME=====\n\n");
}

//Receives a game
//Outputs a game with a swipe up
int swipe_up(int board[])
{
	int repeat = 0, num_changes = 0;
	int has_merged[board_size * board_size];
	memset(has_merged, 0, sizeof(int) * board_size * board_size);

  for (int i=board_size; i<board_size*board_size; i++)
  {
    if(board[i] == 0)
    {
      continue;
    }

    repeat = i-board_size;
    while(repeat / board_size > 0 && board[repeat] == 0)
    {
      repeat -= board_size;
    }
    
    if(board[repeat] == 0)
    {
      board[repeat] = board[i];
      board[i] = 0;
      num_changes++;
    }
    else if(board[repeat] == board[i] && has_merged[repeat] == 0)
    {
      board[repeat] = board[i] << 1;
      board[i] = 0;
      has_merged[repeat] = 1;
      num_changes++;
    }
    else if(repeat < i-board_size)
    {
      board[repeat+board_size] = board[i];
      board[i] = 0;
      num_changes++;
    }
  }

  return num_changes;
}

//Receives a game
//Outputs a game with a swipe down
int swipe_down(int board[])
{
	int repeat = 0, num_changes = 0;
	int has_merged[board_size * board_size];
	memset(has_merged, 0, sizeof(int) * board_size * board_size);

  for(int i = board_size*board_size-board_size-1; i > -1; i--)
  {
    if(board[i] == 0)
    {
      continue;
    }

    repeat = i+board_size;
    while(repeat / board_size < board_size-1 && board[repeat] == 0)
    {
      repeat += board_size;
    }

    if(board[repeat] == 0)
    {
      board[repeat] = board[i];
      board[i] = 0;
      num_changes++;
    }
    else if(board[repeat] == board[i] && has_merged[repeat] == 0)
    {
      board[repeat] = board[i] << 1;
      board[i] = 0;
      has_merged[repeat] = 1;
      num_changes++;
    }
    else if(repeat > i+board_size)
    {
      board[repeat-board_size] = board[i];
      board[i] = 0;
      num_changes++;
    }
  }

  return num_changes;
}

//Receives a game
//Outputs a game with a swipe left
int swipe_left(int board[])
{
	int repeat = 0, num_changes = 0;
	int has_merged[board_size * board_size];
	memset(has_merged, 0, sizeof(int) * board_size * board_size);

  for(int i=1; i<board_size*board_size; i++)
  {
    if(i % board_size == 0)
    {
      i++;
    }

    if(board[i] == 0)
    {
      continue;
    }

    repeat = i-1;
    while(repeat % board_size != 0 && board[repeat] == 0)
    {
      repeat--;
    }

    if(board[repeat] == 0)
    {
      board[repeat] = board[i];
      board[i] = 0;
      num_changes++;
    }
    else if(board[repeat] == board[i] && has_merged[repeat] == 0)
    {
      board[repeat] = board[i] << 1;
      board[i] = 0;
      has_merged[repeat] = 1;
      num_changes++;
    }
    else if(repeat < i-1)
    {
      board[repeat+1] = board[i];
      board[i] = 0;
      num_changes++;
    }
  }

  return num_changes;
}

//Receives a game
//Outputs a game with a swipe right
int swipe_right(int board[])
{
	int repeat = 0, num_changes = 0;
	int has_merged[board_size * board_size];
	memset(has_merged, 0, sizeof(int) * board_size * board_size);

  for(int i=board_size*board_size-2; i > -1; i--)
  {
    if(i % board_size == board_size - 1)
    {
      i--;
    }

    if(board[i] == 0)
    {
      continue;
    }

    repeat = i+1;
    while(repeat % board_size != board_size - 1 && board[repeat] == 0)
    {
      repeat++;
    }

    if(board[repeat] == 0)
    {
      board[repeat] = board[i];
      board[i] = 0;
      num_changes++;
    }
    else if(board[repeat] == board[i] && has_merged[repeat] == 0)
    {
      board[repeat] = board[i] << 1;
      board[i] = 0;
      has_merged[repeat] = 1;
      num_changes++;
    }
    else if(repeat > i+1)
    {
      board[repeat-1] = board[i];
      board[i] = 0;
      num_changes++;
    }
  }

  return num_changes;
}
int check_sol(int curr_board[])
{
	for (int i = 0; i < board_size * board_size; i++)
	{
		if (curr_board[i] == board_values_sum)
		{
			return 1;
		}
	}
	return 0;
}

void copy_prev_board(int curr_board[], int prev_board[])
{
	for (int i = 0; i < board_size * board_size; i++)
	{
		curr_board[i] = prev_board[i];
	}
}

//Function that actually solves the game
//Backtracking using sol_moves (best solution found) and max_moves (maximum possible moves)
void solve_game(int prev_board[], int swipe, int depth)
{
	if (depth > max_moves || depth == sol_moves)
	{
		return;
	}

	int curr_board[board_size * board_size];
  copy_prev_board(curr_board, prev_board);

  int num_changes; // To check if at least one merge occurred in a swipe

	switch (swipe)
	{
	case 1:
		num_changes = swipe_up(curr_board);
		break;
	case 2:
		num_changes = swipe_right(curr_board);
		break;
	case 3:
		num_changes = swipe_down(curr_board);
		break;
	case 4:
		num_changes = swipe_left(curr_board);
		break;
	default:
    num_changes = -1;
		break;
	}

  if(num_changes == 0)
  {
    return;
  }

  if (check_sol(curr_board) == 1)
	{
		sol_moves = depth;
	}
  else
  {
    solve_game(curr_board, 1, depth + 1);
    solve_game(curr_board, 2, depth + 1);
    solve_game(curr_board, 3, depth + 1);
    solve_game(curr_board, 4, depth + 1);
  }
}

//Function that reads the input from stdin and calls solve game for each board
void getInput()
{
	int num_tests = 0;

	scanf("%d", &num_tests);
  
  while(num_tests > 0)
  {
		scanf("%d %d", &board_size, &max_moves);
		board_values_sum = 0;
		sol_moves = -1;

		int board[board_size*board_size];

		//Parse each new line into its columns and store respective values
		for (int j = 0; j < board_size*board_size; j++)
		{
			scanf("%d", &board[j]); // Get tile value
		  board_values_sum += board[j]; // Sum to check if solution was achieved
		}

		solve_game(board, 0, 0);

		if(sol_moves == -1)
		{
			printf("no solution\n");
		}
		else
		{
			printf("%d\n", sol_moves);
		}

    num_tests--;
  }
}

int main()
{
	getInput();
	return 0;
}
