#include <stdio.h>
#include <stdlib.h>
///bubble sort
int main()
{
    int tab[10]={5,32,12,44,6521,23,12,11,99,67};
    int n=10;
    int pomocnicza;
    for(int i=0; i<10; i++)
    {
        printf("%d,", tab[i]);
    }
    printf("\n");
    do{
    for (int i = 0; i < n-1; i++)
        {
            if (tab[i] > tab[i+1])
            {
                pomocnicza=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=pomocnicza;
            }
        }
    n = n-1;}while (n > 1);
    for(int i=0; i<10; i++)
    {
        printf("%d,", tab[i]);
    }
}
///tranpozycja macierzy 5x5
///sortowanie tablicy 2wymiarowej
