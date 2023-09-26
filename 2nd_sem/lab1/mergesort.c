#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void merge(int arr[], int low, int mid, int high)
{
    int copy_arr[high - low + 1];
    for (int i = low; i <= high; i++)
    {
        copy_arr[i - low] = arr[i];
    }
    int l = 0;
    int r = mid - low + 1;
    int i = low;

    while (l <= mid - low && r <= high - low)
    {
        if (copy_arr[l] <= copy_arr[r])
        {
            arr[i] = copy_arr[l];
            l += 1;
        }
        else
        {
            arr[i] = copy_arr[r];
            r += 1;
        }
        i += 1;
    }
    while (l <= mid - low)
    {
        arr[i] = copy_arr[l];
        l += 1;
        i += 1;
    }
    while (r <= high - low)
    {
        arr[i] = copy_arr[r];
        r += 1;
        i += 1;
    }
}

void mergesort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high)/2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
    
}

int main(void)
{
    srand(time(NULL));

    int *arr;

    for (int size = 50000; size <= 1000000; size += 50000)
    {
        arr = (int *)malloc(sizeof(int) * size);
        assert((arr != NULL) && "Memory allocation error 1");

        for (int i = 0; i < size; i++)
            arr[i] = rand() % 10000;


        mergesort(arr, 0, size - 1);

        for (int j = 0; j < size - 1; j++)
        {
            assert((arr[j] <= arr[j + 1]) && "No sorted");
        }


        printf("%d\t%.6lf\t%.6lf\t%.6lf\n", size, 0, 0, 0);
        free(arr);

    }
}