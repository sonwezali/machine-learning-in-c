#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float sigmoidf(float x)
{
    return 1.f/(1.f + expf(-x));
}

// OR-gate
float train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};
#define train_size (sizeof(train)/sizeof(train[0]))

float costFunc(float w1, float w2)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_size; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1 + x2*w2);
        float d = y - train[i][2];
        result += d*d;
    } 
    result /= train_size;
    return result;
}

float rand_float()
{
    return (float) rand() / (float) RAND_MAX;
}

int main()
{
    srand(69);
    float w1 = rand_float();
    float w2 = rand_float();

    float eps = 1e-3;
    float rate = 1e-2;

    for (size_t i = 0; i < 10; i++) {
        float c = costFunc(w1, w2);
        printf("w1 = %f, w2 = %f, c = %f\n", w1, w2, c);
        float dw1 = (costFunc(w1 + eps, w2) - costFunc(w1, w2))/eps;
        float dw2 = (costFunc(w1, w2 + eps) - costFunc(w1, w2))/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
    }

    return 0;
}
