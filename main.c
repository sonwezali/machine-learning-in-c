#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};

float rand_float()
{
    return (float) rand() / (float) RAND_MAX;
}

int main() 
{
    // srand(time(NULL));
    srand(3); // kept as 3 for testing purposes
    // y = x*w;
    float w = rand_float() * 10;

    printf("%f\n", w);
    return 0;
}

