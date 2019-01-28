#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

void wyczysc (char plansza[3][3])
{
    int i,j;
    //if(a==2)
    //{
    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
            plansza[i][j]=' ';
    /*)
    else
    (
        for (i=0;i<5;i++)
        for (j=0;j<5;j++)
            plansza[i][j]=' ';
    )*/

}
void wypisz (char plansza[3][3])
{
    system("cls");

    //if(a==2)
    //{
        printf("[%c][%c][%c]\n",plansza[0][0], plansza[0][1], plansza[0][2]);
        printf("[%c][%c][%c]\n",plansza[1][0], plansza[1][1], plansza[1][2]);
        printf("[%c][%c][%c]\n",plansza[2][0], plansza[2][1], plansza[2][2]);
    /*}
    else
    {
        printf("[%c][%c][%c]\n",plansza[0][0], plansza[0][1], plansza[0][2],plansza[0][3],plansza[0][4]);
        printf("[%c][%c][%c]\n",plansza[1][0], plansza[1][1], plansza[1][2],plansza[1][3],plansza[1][4]);
        printf("[%c][%c][%c]\n",plansza[2][0], plansza[2][1], plansza[2][2],plansza[2][3],plansza[2][4]);
        printf("[%c][%c][%c]\n",plansza[3][0], plansza[3][1], plansza[3][2],plansza[3][3],plansza[3][4]);
        printf("[%c][%c][%c]\n",plansza[4][0], plansza[4][1], plansza[4][2],plansza[4][3],plansza[4][4]);
    }*/

}
void ruch_gracza(char plansza[3][3])
{
    unsigned int i=3, j;
    wypisz(plansza);
    printf("Podaj wiersz i kolumne w ktorej chcesz wstawic krzyzyk\n");
    //if(a==2)
    //{
        while ((i>2)||(j>2) || (plansza[i][j]!=' '))
        scanf("%u %u", &i, &j);
    /*}
    else
    (
        while ((i>4)||(j>4) || (plansza[i][j]!=' '))
    )*/
    plansza[i][j]='x';
}

void ruch_komputera(char plansza[3][3])
{
    unsigned int i=3, j;
    wypisz(plansza);
    //if(a==2)
    //{
        while ((i>2)||(j>2) || (plansza[i][j]!=' '))
        {
            for (i=0;i<3;i++)
            {
                for (j=0;j<3;j++)
                {
                    if(plansza[i][j]=='o')
                    {
                        if(plansza[i][j+1]=='o')
                        {
                            if(j==0)
                                if(plansza[i][j+2]==' ')
                                    {plansza[i][j+2]='o';
                                    return;}
                            else{
                                if(plansza[i][j-1]==' ')
                                    {plansza[i][j+2]='o';
                                    return;}}
                        }
                        else if(plansza[i+1][j]=='o')
                        {
                            if(i==0)
                                if(plansza[i+2][j]==' ')
                                    {plansza[i+2][j]='o';
                                    return;}
                            else{
                                if(plansza[i-1][j]==' ')
                                    {plansza[i-1][j]='o';
                                    return;}}
                        }
                        else if(plansza[i+1][j+1]=='o')
                        {
                            if(i==0&&j==0)
                                if(plansza[i+2][j+2]==' ')
                                    {plansza[i+2][j+2]='o';
                                    return;}
                            else{
                                if(plansza[i-1][j-1]==' ')
                                {
                                    plansza[i-1][j-1]='o';
                                    return;
                                }}

                        }
                    }
                }
            }
            for (i=0;i<3;i++)
            {
                for (j=0;j<3;j++)
                {
                    if(plansza[i][j]=='x')
                    {
                        if(plansza[i][j+1]=='x')
                        {
                            if(j==0)
                                if(plansza[i][j+2]==' ')
                                    {plansza[i][j+2]='o';
                                    return;}
                            else{
                                if(plansza[i][j-1]==' ')
                                    {plansza[i][j+2]='o';
                                    return;}}
                        }
                        else if(plansza[i+1][j]=='x')
                        {
                            if(i==0)
                                if(plansza[i+2][j]==' ')
                                    {plansza[i+2][j]='o';
                                    return;}
                            else{
                                if(plansza[i-1][j]==' ')
                                    {plansza[i-1][j]='o';
                                    return;}}
                        }
                        else if(plansza[i+1][j+1]=='x')
                        {
                            if(i==0&&j==0)
                                if(plansza[i+2][j+2]==' ')
                                    {plansza[i+2][j+2]='o';
                                    return;}
                            else{
                                if(plansza[i-1][j-1]==' ')
                                {
                                    plansza[i-1][j-1]='o';
                                    return;
                                }}

                        }

                        }
                    }
                }

            int sukces=0;
            do
            {
                i=rand()%3;
                j=rand()%3;
                if(plansza[i][j]!='x'&&plansza[i][j]!='o')
                {
                    printf("asa");

                    plansza[i][j]='o';
                    sukces=1;
                }

            }while (sukces==0);
            return;



plansza[i][j]='o';
        }
    }
    /*}
    else
    (
        while ((i>4)||(j>4) || (plansza[i][j]!=' '))
    )*/
    //



int main()
{
    int a;

    printf("Podaj liczbe rozmiar 3 lub 5 ");
    scanf ("%d", &a);
    a--;
    char plansza[a][a];
    int wynik =0;


    wyczysc(plansza);
    while(wynik==0)
    {
        ruch_gracza(plansza);
        ruch_komputera(plansza);

    }



    return 0;
}
