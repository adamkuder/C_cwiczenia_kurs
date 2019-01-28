#include <stdio.h>
#include <stdlib.h>
int binarySearch(int arr[], int l, int r, int x)
{
   if (r>=l)
   {
        int srodek = l + (r-l)/2;
        if (arr[srodek] == x)  return srodek;
        if (arr[srodek] > x) return binarySearch(arr, l, srodek-1, x);

        return binarySearch(arr, srodek+1, r, x);
   }

   return -1;
}

int main(void)
{
   int arr[] = {3,4,5,6,6,7,8,9,10,54,56,77,81,90,100};
   int n = sizeof(arr)/ sizeof(arr[0]);
   int szukany = 10;
   int wynik = binarySearch(arr, 0, n-1, szukany);
   (wynik==-1)? printf("nie znaleziono")
                 : printf("znaleziono %d", wynik);
   return 0;
}
