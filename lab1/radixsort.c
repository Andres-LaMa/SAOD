#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 100
#define RANG 10000

void radixsort(int arr[], int n)
{
    for (int k = 1; k <= 10000; k *= 10)
    {
        int output[n];
        int count[10] = {0};
        for (int i = 0; i < n; i++)
        {
            count[ arr[i] / k % 10 ] += 1;
        }
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[ i - 1];
        }
        int c = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            c = arr[i] / k % 10;
            output[ count[c] - 1 ] = arr[i];
            count[c]--;
        }
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
        printf("\n");
    }
    for (int i = 1; i < n; i++)
    {
        assert( (arr[i] >= arr[i - 1]) && "NO SORTED");
    }
}

int main(void)
{
    int *arr;
    arr = (int *)malloc(sizeof(int) * 100);

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % RANG;
    }
    for (int i = 0; i < SIZE; i++)
    {
        assert((arr[i] < RANG && arr[i] >= 0) && "High");
    }

    radixsort(arr, SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}