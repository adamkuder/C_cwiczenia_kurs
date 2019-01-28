 #include <stdio.h>
 #include <stdlib.h>

 int main ()
 {
     FILE * pFile;
     //int n;
     //char name [100];
     int a,b;
     printf("Podaj liczbe na start ");
     scanf ("%d", &a);
     printf("Podaj liczbe iteracji ");
     scanf ("%d", &b);
     pFile = fopen ("myfile.txt","w");
     //printf ("Podaj Imie i Nazwisko ");
     //gets (name);
     for (int i=a; i<=b; i++)
     {
         fprintf (pFile, "%d \n",i);    //%s jesli string
     }

     fclose (pFile);
     return 0;
 }
