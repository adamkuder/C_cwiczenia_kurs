#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{
    int *t=a;
    *a=b;
    *b=t;
}
int part(int arr[], int left, int right)
{
    int pivot=arr[right];
    int i=(left-1);
    for (int j=left; j<=right-1; j++)

        if (arr[j]<=pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[right]);
    return (i+1);
void quickSort(int arr[], int left, int right)
{
    if (left<right)
    {
        int p=part(arr[],left,right);
        quickSort(arr, left, p-1);
        quickSort(arr,  p+1, right);
    }
}
int main()
{
    int tab[]={23,11,543,2,12,5,2332,54,213,532,123,512,432};
    quickSort(tab, 0,12);
    for(int i=0; i<=6; i++)
    {
        printf("%d ", tab[i]);
    }

    return 0;
}
