#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int numbers[6];
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
        {
            numbers[i] = 0;
        }
        else
        {
            numbers[i] = pow(2, i);
        }
    }

    srand(time(0));
    if (argc < 5)
    {
        printf("./testgenerator <ntestes> <filename> <maxboardsize> <maxmaxmoves>");
        return 0;
    }
    else
    {
        int ntests = atoi(argv[1]);
        int maxboardsize = atoi(argv[3]);
        int maxmaxmoves = atoi(argv[4]);

        printf("Number of tests chosen %d\n", ntests);

        FILE *fp = fopen(argv[2], "w+");

        fprintf(fp, "%d\n", ntests);

        int board_size, max_moves;
        for (int i = 0; i < ntests; i++)
        {
            board_size = rand() % maxboardsize;
            max_moves = rand() % maxmaxmoves;
            fprintf(fp, "%d %d\n", board_size, max_moves);
            for (int j = 0; j < board_size; j++)
            {
                for (int k = 0; k < board_size; k++)
                {
                    fprintf(fp, "%d ", numbers[rand() % 6]);
                }
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    return 0;
}