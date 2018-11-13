#include <stdio.h>
#include <stdlib.h>
int sumdivo(int n)
{
    int divo=0;
    for (int i=1;i<=n;i++)
        if (n%i==0)
        {
            //printf("%d ",i);
            divo=divo+i;
        }
    divo =divo-n;
    return divo;
}

int main()
{
    int a,b;
    printf("Podaj liczbe a ");
    scanf ("%d", &a);

    int sumdivorsA, sumdivorsB;
    sumdivorsA=sumdivo(a);
    //printf("\nLiczba Skojarzona to  %d \n", sumdivorsA);
    /*
    for(int i=1; i<=sumdivorsA; i++)
    {
        sumdivorsB=sumdivo(i);
        if(a==sumdivorsB && i== sumdivorsA )
        {
            printf("\nLiczba Skojarzona to  %d \n", i-1);
            znaleziono++;
        }

    }*/
    sumdivorsB=sumdivo(sumdivorsA-1);
    if(sumdivorsB==a+1)
    {
        printf("Znalazlem liczbe %d \n", sumdivorsA-1);
    }
    else
    {
        printf("Nie znalazlem liczby");
    }
    return 0;
}
