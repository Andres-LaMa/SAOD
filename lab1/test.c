#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 1000

double wtime()
{
struct timeval t;
gettimeofday(&t, NULL);
return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void test(int arr[], int n)
{
    for (int k = 1; k <= 100; k *= 10)
    {
        int output[SIZE];
        int count[10] = {0};
        for (int i = 0; i < n; i++)
        {
            count[ arr[i] / k % 10 ] += 1;
        }
        for (int i = 1; i < n; i++)
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
}

int main(void)
{
    srand(time(NULL));

    int k_el = 1000;

    int *arr = malloc(k_el * sizeof(int));

    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand() % 1000;
    }
    for (int i = 0; i < 100; i++)
    {
        assert((arr[i] < 1000000000000 && arr[i] >= 0) && "High");

    }
    printf("\n");

    double rtime = wtime();

    test(arr, k_el);

    for (int i = 1; i < 100; i++)
    {
        assert( (arr[i] >= arr[i - 1]) && "NO SORTED");
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    rtime -= wtime();
    printf("%lf \n", rtime);
    
    
}