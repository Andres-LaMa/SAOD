#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
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

int main(void)
{
    srand(time(NULL));

    int *arr;
    arr = (int *)malloc(sizeof(int) * 1000000);

    for (int i = 0; i < 1000000; i++)
    {
        arr[i] = rand() % 10;
    }
    for (int i = 0; i < 1000000; i++)
    {
        assert((arr[i] < 10000 && arr[i] >= 0) && "High");
    }

    double time = wtime();
    mergesort(arr, 0, 1000000 - 1);
    printf("%lf\n", time - wtime());
    

    for (int i = 0; i < 1000000 - 1; i++)
    {
        assert((arr[i] <= arr[i + 1]) && "No sorted");
    }
    free(arr);
}