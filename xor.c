#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float or_w1, or_w2, or_b;
    float nand_w1, nand_w2, nand_b;
    float and_w1, and_w2, and_b;
} Xor;

float sigmoidf(float x)
{
    return 1.f/(1.f + expf(-x));
}

float forward(Xor m, float x1, float x2)
{
    float a = sigmoidf(m.or_w1*x1 + m.or_w2*x2 + m.or_b);
    float b = sigmoidf(m.nand_w1*x1 + m.nand_w2*x2 + m.nand_b);

    return sigmoidf(m.and_w1*a + m.and_w2*b + m.and_b);
}

float xor_train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};

float (*train)[3] = xor_train;
size_t train_size = 4;

float costFunc(Xor m)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_size; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(m, x1, x2);
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

Xor rand_xor()
{
    Xor m = {
        .or_w1 = rand_float(),
        .or_w2 = rand_float(),
        .or_b = rand_float(),

        .nand_w1 = rand_float(),
        .nand_w2 = rand_float(),
        .nand_b = rand_float(),

        .and_w1 = rand_float(),
        .and_w2 = rand_float(),
        .and_b = rand_float(),
    };

    return m;
}

void print_xor(Xor m)
{
    printf("OR:   w1: %f, w2: %f, b: %f\n", m.or_w1, m.or_w2, m.or_b);
    printf("NAND: w1: %f, w2: %f, b: %f\n", m.nand_w1, m.nand_w2, m.nand_b);
    printf("AND:  w1: %f, w2: %f, b: %f\n", m.and_w1, m.and_w2, m.and_b);
}

int main()
{
    Xor m = rand_xor();
    print_xor(m);

    return 0;
}
