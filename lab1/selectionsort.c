#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 10

void selectionsort(int arr[], int n)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        int min = i;
        for (int j = i+1; j < SIZE; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;
            }   
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

    }
}

int main(void)
{
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 1000;
    }
    for (int i = 0; i < SIZE; i++)
    {
        assert((arr[i] < 1000 && arr[i] >= 0) && "High");
    }

    selectionsort(arr, SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}