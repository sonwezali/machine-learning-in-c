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

float costFunc(float w, float b)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_size; i++) {
        float x = train[i][0];
        float y = x*w + b;
        float d = y - train[i][1];
        result += d*d;
    } 
    result /= train_size;
    return result;
}

int main() 
{
    srand(time(0));
    // y = x*w;
    float w = rand_float()*10.0f;
    float b = rand_float()*5.0f;

    float eps = 1e-3;
    float rate = 1e-3;

    printf("%f\n", costFunc(w, 0));
    for (size_t i = 0; i < 500; i++) {
        float dCost = (costFunc(w + eps, 0) - costFunc(w, 0))/eps;
        w -= rate*dCost; // Finite difference
        printf("cost = %f, w = %f\n", costFunc(w, 0), w);
    }
    printf("---------------------------\n");
    printf("w: %f\n", w);

    return 0;
}

