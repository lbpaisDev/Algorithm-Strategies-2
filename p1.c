#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0

//Estrategias Algoritmicas 2020/2021
//Afonso Magalhães 2016228735
//Leandro Pais 2017251509

int board_size = 0;                   // Size of board in a single dimension
int board_values_sum = 0;             // Sum to check if solution was achieved
int max_moves = 0;                    // Max moves possible on a board
int sol_moves = -1;                   // Value of best solution found
int number_of_merges[4] = {0};        // Array of num of changes for each swipe
int ordered_swipes[4] = {1, 2, 3, 4}; // Array of num of changes for each swipe

//Swipes down the matrix
int swipe_down(int board[board_size][board_size])
{

  int repeat = 0;      //move tiles
  int has_changed = 0; //check if the swipe is effective

  //Keeps information about the tiles when it comes to merging
  int has_merged[board_size][board_size];
  memset(has_merged, 0, sizeof(int) * board_size * board_size);

  int i, j;
  //Rows
  for (i = board_size - 2; i > -1; i--)
  {
    //Columns
    for (j = 0; j < board_size; j++)
    {
      //If tile is 0 is empty and do nothing
      if (board[i][j] == 0)
      {
        continue;
      }

      //Find out where to move the current tile
      repeat = i + 1;
      while (repeat < board_size - 1 && board[repeat][j] == 0)
      {
        repeat++;
      }

      //If target tile is empty just put the current one there
      if (board[repeat][j] == 0)
      {
        board[repeat][j] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }

      //Else if the value is the same of the current and current has not merged
      //Allow merging
      else if (board[repeat][j] == board[i][j] && has_merged[repeat][j] == 0)
      {
        //Count number of merges ocurring
        number_of_merges[0]++;

        board[repeat][j] = board[i][j] << 1;

        //Check if a solution is achieved
        if (board[repeat][j] == board_values_sum)
        {
          return -1;
        }

        board[i][j] = 0;
        has_merged[repeat][j] = 1;
        has_changed = 1;
      }

      //Else just move the nearest empty tile
      else if (repeat > i + 1)
      {
        board[repeat - 1][j] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }
    }
  }

  return has_changed;
}

//Swipes up the matrix
int swipe_up(int board[board_size][board_size])
{
  int repeat = 0;      //move the values
  int has_changed = 0; //check if swipe is effective

  //Keeps values to check if the tile has already merged
  int has_merged[board_size][board_size];
  memset(has_merged, 0, sizeof(int) * board_size * board_size);

  int i, j;
  //Rows
  for (i = 1; i < board_size; i++)
  {
    //Ccolumns
    for (j = 0; j < board_size; j++)
    {
      //If the value is 0 tile is empty
      if (board[i][j] == 0)
      {
        continue;
      }

      //Where the tilves should be moved to
      repeat = i - 1;
      while (repeat > 0 && board[repeat][j] == 0)
      {
        repeat--;
      }

      //If target tile is empty just move
      if (board[repeat][j] == 0)
      {
        board[repeat][j] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }

      //If target tile is not empty and the value is the same as the current and the current hasn't merged
      //Allow merging
      else if (board[repeat][j] == board[i][j] && has_merged[repeat][j] == 0)
      {
        //Count number of merges ocurring
        number_of_merges[1]++;

        board[repeat][j] = board[i][j] << 1;

        //Check if solution was achieved
        if (board[repeat][j] == board_values_sum)
        {
          return -1;
        }

        board[i][j] = 0;
        has_merged[repeat][j] = 1;
        has_changed = 1;
      }
      //Otherwise just move it to the tile before that one that is empty
      else if (repeat < i - 1)
      {
        board[repeat + 1][j] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }
    }
  }

  return has_changed;
}

//swipes left the matrix
int swipe_left(int board[board_size][board_size])
{
  int repeat = 0;      //move tiles
  int has_changed = 0; //check if swipe is effective

  //Keeps info about the tiles (if one particular tile has merged)
  int has_merged[board_size][board_size];
  memset(has_merged, 0, sizeof(int) * board_size * board_size);

  int i, j;
  //Rows
  for (i = 0; i < board_size; i++)
  {
    //Columns
    for (j = 1; j < board_size; j++)
    {
      //If tile is zero then its empty do nothing
      if (board[i][j] == 0)
      {
        continue;
      }

      //Get target tile
      repeat = j - 1;
      while (repeat > 0 && board[i][repeat] == 0)
      {
        repeat--;
      }

      //If target tile is empty just move it there
      if (board[i][repeat] == 0)
      {
        board[i][repeat] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }

      //Else if the value is the same as the current and the current has not merged
      //Allow merging
      else if (board[i][repeat] == board[i][j] && has_merged[i][repeat] == 0)
      {
        //Number of merges ocurring
        number_of_merges[2]++;

        board[i][repeat] = board[i][j] << 1;

        //Check if solution was achieved
        if (board[i][repeat] == board_values_sum)
        {
          return -1;
        }

        board[i][j] = 0;
        has_merged[i][repeat] = 1;
        has_changed = 1;
      }

      //Else just move it to the nearest empty tile
      else if (repeat < j - 1)
      {
        board[i][repeat + 1] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }
    }
  }

  return has_changed;
}

//swipes right the matrix
int swipe_right(int board[board_size][board_size])
{
  int repeat = 0;      //Move values
  int has_changed = 0; //check if swipe is effective

  //Keeps info about the tile (if it has merged previously in this swipe)
  int has_merged[board_size][board_size];
  memset(has_merged, 0, sizeof(int) * board_size * board_size);

  int i, j;
  //Rows
  for (i = 0; i < board_size; i++)
  {
    //Columns
    for (j = board_size - 2; j > -1; j--)
    {
      //If tile is empty do nothing
      if (board[i][j] == 0)
      {
        continue;
      }

      //Get target tile
      repeat = j + 1;
      while (repeat < board_size - 1 && board[i][repeat] == 0)
      {
        repeat++;
      }

      //If target tile is empty just move the current on there
      if (board[i][repeat] == 0)
      {
        board[i][repeat] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }

      //Else if the values is the same as the current one and current one as not merged
      //Allow merging
      else if (board[i][repeat] == board[i][j] && has_merged[i][repeat] == 0)
      {
        //Number of merges ocurring
        number_of_merges[3]++;

        board[i][repeat] = board[i][j] << 1;

        //Check if solution is achieved
        if (board[i][repeat] == board_values_sum)
        {
          return -1;
        }

        board[i][j] = 0;
        has_merged[i][repeat] = 1;
        has_changed = 1;
      }

      //Otherwise move it to the nearest empty tile
      else if (repeat > j + 1)
      {
        board[i][repeat - 1] = board[i][j];
        board[i][j] = 0;
        has_changed = 1;
      }
    }
  }

  return has_changed;
}

//Copy game matrix
//Important to keep a common board at each recursion level
void copy_prev_board(int curr_board[board_size][board_size], int prev_board[board_size][board_size])
{
  //Rows
  for (int i = 0; i < board_size; i++)
  {
    //Columns
    for (int j = 0; j < board_size; j++)
    {
      //Copy
      curr_board[i][j] = prev_board[i][j];
    }
  }
}

//Print game
void print_game(int board[board_size][board_size])
{

  printf("\n\t=====CURRENT GAME=====\n");
  printf("\tBoard Size: %d\tMax moves: %d\n", board_size, max_moves);
  for (int i = 0; i < board_size; i++)
  {
    for (int j = 0; j < board_size; j++)
    {
      printf("\t%d", board[i][j]);
    }
    printf("\n");
  }
  printf("\t=====END OF CURRENT GAME=====\n\n");
}

void get_best_swipe(int board[board_size][board_size])
{
  //Reset arrays
  memset(number_of_merges, 0, sizeof(int) * 4);
  for (int i = 0; i < 4; i++)
  {
    ordered_swipes[i] = i + 1;
  }
  if (DEBUG == 1)
  {
    print_game(board);
  }

  if (DEBUG == 1)
  {
    printf("Number of merges\n");
    for (int i = 0; i < 4; i++)
    {
      printf("%d ", number_of_merges[i]);
    }
    printf("\n");
    printf("Unordered swipes\n");
    for (int i = 0; i < 4; i++)
    {
      printf("%d ", ordered_swipes[i]);
    }
    printf("\n");
  }

  int merges_0 = 0;
  for (int i = 0; i < 4; i++)
  {
    if (number_of_merges[i] == 0)
    {
      merges_0++;
    }
  }
  if (merges_0 == 4)
  {
    ordered_swipes[0] = 4;
    ordered_swipes[1] = 3;
    ordered_swipes[2] = 1;
    ordered_swipes[3] = 2;
    return;
  }

  //Yes bubblesort, arrays have a fixed value of 4
  //not so inefficient, i guess?
  //don't know if it makes sense
  int temp;
  for (int i = 0; i < 4 - 1; i++)
  {
    for (int j = 0; j < 4 - i - 1; j++)
    {
      if (number_of_merges[j] < number_of_merges[j + 1])
      {
        temp = number_of_merges[j];
        number_of_merges[j] = number_of_merges[j + 1];
        number_of_merges[j + 1] = temp;

        temp = ordered_swipes[j];
        ordered_swipes[j] = ordered_swipes[j + 1];
        ordered_swipes[j + 1] = temp;
      }
    }
  }
    
  if (DEBUG == 1)
  {
    printf("ordered swipes\n");
    for (int i = 0; i < 4; i++)
    {
      printf("%d ", ordered_swipes[i]);
    }
    printf("\n");
  }
}

//Function that actually solves the game
//Backtracking using sol_moves (best solution found) and max_moves (maximum possible moves)
void solve_game(int board[board_size][board_size], int swipe, int depth)
{
  //best solution implementation
  if (depth > max_moves || depth == sol_moves)
  {
    return;
  }

  //Copy board for each recursion level
  int curr_board[board_size][board_size];
  copy_prev_board(curr_board, board);

  int has_changed; // To check if at least one merge occurred in a swipe

  //Branching
  switch (swipe)
  {
  case 1:
    has_changed = swipe_down(curr_board);
    break;
  case 2:
    has_changed = swipe_up(curr_board);
    break;
  case 3:
    has_changed = swipe_left(curr_board);
    break;
  case 4:
    has_changed = swipe_right(curr_board);
    break;
  default:
    has_changed = -2;
    break;
  }
  //If board doesn't change just end branch
  if (has_changed == 0)
  {
    return;
  }

  //if solution was found update solmoves
  if (has_changed == -1)
  {
    sol_moves = depth;
    return;
  }

  if (DEBUG == 1)
  {
    printf("Order of calls at depth: %d\n", depth);
  }

  //Recursive calls
  solve_game(curr_board, 1, depth + 1);
  solve_game(curr_board, 2, depth + 1);
  solve_game(curr_board, 3, depth + 1);
  solve_game(curr_board, 4, depth + 1);
}

int main()
{
  //Num tests
  int num_tests = 0;
  scanf("%d", &num_tests);

  //Solve number of tests
  while (num_tests > 0)
  {
    //Get board size and max moves from first line
    scanf("%d %d", &board_size, &max_moves);

    //Reset global params
    board_values_sum = 0;
    sol_moves = -1;

    int board[board_size][board_size]; // Board
    int max = 0;                       // Max value in board

    //Rows
    for (int i = 0; i < board_size; i++)
    {
      //Columns
      for (int j = 0; j < board_size; j++)
      {
        scanf("%d", &board[i][j]); // Get tile value

        if (board[i][j] != 0) // If tile value different than 0, update sum and max vars
        {
          board_values_sum += board[i][j];

          //Get max tile value for later pre processing
          if (board[i][j] > max)
          {
            max = board[i][j];
          }
        }
      }
    }

    //Pre processing if this is the case the board is unsolvable
    //Recursive call isn't even made
    if (max > board_values_sum / 2)
    {
      printf("no solution\n");
    }

    //Other wise
    else
    {
      //First call
      solve_game(board, 0, 0);

      //Check sol_moves set to -1 if there's no solution
      if (sol_moves == -1)
      {
        printf("no solution\n");
      }
      else
      {
        printf("%d\n", sol_moves);
      }
    }

    num_tests--;
  }
  return 0;
}