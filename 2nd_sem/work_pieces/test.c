#include <stdio.h>
#include <string.h>

int main()
{
    char *one[] = {"Fox", "Fox", "leF"};

    for (short i = 0; i < 2; i++)
    {
        if (strcmp(one[i],one[i+1]) == 0)
        {
            printf("Первая и вторая строка равны\n");
        }
        else
        {
            printf("Первая и вторая строка не равны\n");
        }
    }
    
    
}