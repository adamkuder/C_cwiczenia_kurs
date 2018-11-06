#include <stdio.h>
#include <stdlib.h>
///wype³nienie inne niz obudowa np wypelnienie * a obodowa /
void rysowanie(int  *ilosc_poziomow,int *szerokosc_pierwszego)
{
    int szerokosc_choinki;
    szerokosc_choinki=*szerokosc_pierwszego*(*ilosc_poziomow*2);
    for(int i=1; i<=*ilosc_poziomow; i++)///rysowanie choinki rozpoczynamy od ilosci poziomow
    {
        int temp_spacje=(szerokosc_choinki/4)-i;///obliczanie potrzebnych spacji
                for (int h=0; h<=*szerokosc_pierwszego; h++)
                {

                    for(int k=0; k<=temp_spacje; k++)
                    {
                        printf(" ");
                    }
                    temp_spacje--;
                    printf("z");
                    for (int l=0; l<=h+((i-1)*2); l++)
                    {
                        printf("*");
                    }
                    printf("a");
                    printf("\n");
                    h++;

                }
    }
    ///Pien
    for(int i=2; i<=*ilosc_poziomow;i++)
    {
        int temp_spacje=((szerokosc_choinki/4)-*ilosc_poziomow+2);
        for(int k=0; k<=temp_spacje; k++)
        {
            printf(" ");
        }
        for (int l=0; l<=*ilosc_poziomow; l++)
        {
            printf("|");
        }
        printf("\n");

    }
}
int main()
{
    int ilosc_poziomow;
    int szerokosc_pierwszego;
    printf("Podaj ilosc poziomow ");
    scanf ("%d", &ilosc_poziomow);
    printf("Podaj szerokosc pierwszego ");
    scanf ("%d", &szerokosc_pierwszego);

    rysowanie(&ilosc_poziomow,&szerokosc_pierwszego);
    return 0;
}
