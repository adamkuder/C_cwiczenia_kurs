#include <stdio.h>
#include <stdlib.h>
int fibo(int f)
{
    if (f<=2)
    {
        return 1;
    }
    return fibo(f-1)+fibo(f-2);
}

int main()
{
    int z=fibo(7);
    printf("%d ", z );
    return 0;
}
