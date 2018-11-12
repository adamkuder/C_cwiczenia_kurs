#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int x=10;
    int y=10;
    int tab[x][y];
    for (int i=0; i<x; i++)
    {
        for(int j=0; i<y; j++)
        {
            tab[i][j]=rand() % 100;
            printf("%d,", tab[i][j]);
        }

    }
    printf("\n");
    ///dominanta
    int tabdom[x];
    int countdommax=1;
    for (int i=0; i<x; i++)
    {
        int tempdom=0;
        for(int j=i; j<x; j++)
        {
            if (tab[i]==tab[j])
            {
                tempdom++;
            }
        }
        tabdom[i]=tempdom;
        if (countdommax<tempdom){countdommax=tempdom;}

    }
    if (countdommax>1)
    {
        for (int i=0; i<x; i++)
        {

            if (countdommax==tabdom[i])
            {
                printf("dominanta = %d,", tab[i]);
                printf(" ilosc wystapien = %d", tabdom[i]);
                printf("\n");
            }
        }
    }
    else
    {
        printf("brak dominaty");
    }
    return 0;
}
