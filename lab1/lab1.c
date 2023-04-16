#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

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
    }
    for (int i = 1; i < n; i++)
    {
        assert( (arr[i] >= arr[i - 1]) && "NO SORTED");
    }
}

void selectionsort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i+1; j < n; j++)
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
    int *arr1, *arr2, *arr3;
    double tradix, tselection, tmerge;

    printf("Size\tRadix     \tSelection \tMerge     \n");

    for (int size = 50000; size <= 1000000; size += 50000)
    {
        arr1 = (int *)malloc(sizeof(int) * size);
        assert((arr1 != NULL) && "Memory allocation error 1");

        arr2 = (int *)malloc(sizeof(int) * size);
        assert((arr1 != NULL) && "Memory allocation error 2");

        arr3 = (int *)malloc(sizeof(int) * size);
        assert((arr1 != NULL) && "Memory allocation error 3");

        for (int i = 0; i < size; i++)
            arr1[i] = arr2[i] = arr3[i] = rand() % 10000;
        
        tradix = wtime();
        radixsort(arr1, size);
        tradix = wtime() - tradix;

        for (int j = 0; j < 10000; j++)
        {
            assert((arr1[j] <= arr1[j + 1]) && "No sorted");
        }

        free(arr1);

        tselection = wtime();
        selectionsort(arr2, size);
        tselection = wtime() - tselection;

        for (int j = 0; j < 10000; j++)
        {
            assert((arr2[j] <= arr2[j + 1]) && "No sorted");
        }

        free(arr2);

        tmerge = wtime();
        mergesort(arr3, 0, size - 1);
        tmerge = wtime() - tmerge;

        for (int j = 0; j < 10000; j++)
        {
            assert((arr3[j] <= arr3[j + 1]) && "No sorted");
        }

        free(arr3);

        printf("%d\t%.6lf\t%.6lf\t%.6lf\n", size, tradix, tselection, tmerge);
    }
    return 0;
    
}