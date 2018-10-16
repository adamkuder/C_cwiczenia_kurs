#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int x=5;
    int y=4;
    int tab[x][y];
    int tabtrans[y][x];
    for (int i=0; i<y; i++)
    {
        for (int j=0; j<x; j++)
        {
            tab[i][j]=rand() % 100;
            tabtrans[j][i]=tab[i][j];
            printf("%d,", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for (int i=0; i<x; i++)
    {
        for (int j=0; j<y; j++)
        {
            printf("%d,", tabtrans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
