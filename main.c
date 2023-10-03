#include <stddef.h>
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
#define train_size (sizeof(train)/sizeof(train[0]))

float rand_float()
{
    return (float) rand() / (float) RAND_MAX;
}

float costFunc(float w)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_size; i++) {
        float x = train[i][0];
        float y = x*w;
        float d = y - train[i][1];
        result += d*d;
    } 
    result /= train_size;
    return result;
}

int main() 
{
    //srand(time(0));
    srand(3); // kept as 3 for testing purposes
    // y = x*w;
    float w = rand_float()*10;

    float eps = 1e-3;
    float rate = 1e-3;

    printf("%f\n", costFunc(w));
    for (size_t i = 0; i < 500; i++) {
        float dCost = (costFunc(w + eps) - costFunc(w))/eps;
        w -= rate*dCost; // Finite difference
        printf("%f\n", costFunc(w));
    }
    printf("---------------------------\n");
    printf("w: %f\n", w);

    return 0;
}

