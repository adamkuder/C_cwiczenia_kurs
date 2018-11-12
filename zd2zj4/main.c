#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, reverse = 0;
    printf("Podaj liczbe ");
    scanf ("%d", &n);
    int tempn=n;
    while (tempn != 0)
    {
        reverse = reverse * 10;
        reverse = reverse + tempn%10;
        tempn = tempn/10;
    }
    printf("Wspak = %d\n", reverse);
    printf("Liczba = %d\n", n);
    if (reverse==n)
    {
        printf("Podana liczba jest taka sama jak od przodu");

    }
    else
    {
        printf("Podana liczba NIE jest taka sama jak od przodu");
    }
    return 0;
}
