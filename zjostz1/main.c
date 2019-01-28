#include <stdio.h>
#include <stdlib.h>
int silnia(int s)
{
    if (s<=1)
    {
        return 1;
    }
    return silnia(s-1)*s;
}

int main()
{
    int z=silnia(5);
    printf("%d ", z );
    return 0;
}
