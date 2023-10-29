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

// AND/OR/NAND-gate
float and_train[][3] = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1},
};

float or_train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

float nand_train[][3] = {
    {0, 0, 1},
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

Xor learn(Xor m, Xor g, float rate)
{
    m.or_w1 -= rate*g.or_w1;
    m.or_w2 -= rate*g.or_w2;
    m.or_b -= rate*g.or_b;

    m.nand_w1 -= rate*g.nand_w1;
    m.nand_w2 -= rate*g.nand_w2;
    m.nand_b -= rate*g.nand_b;

    m.and_w1 -= rate*g.and_w1;
    m.and_w2 -= rate*g.and_w2;
    m.and_b -= rate*g.and_b;

    return m;
}

Xor finite_diff(Xor m)
{
    Xor g; // gradient
    float c = costFunc(m);
    float saved;
    float eps = 1e-1;

    saved = m.or_w1;
    m.or_w1 += eps;
    g.or_w1 = (costFunc(m) - c)/eps;
    m.or_w1 = saved; // m.or_w1 -= eps; would cause error accumulation since we r working w floats

    saved = m.or_w2;
    m.or_w2 += eps;
    g.or_w2 = (costFunc(m) - c)/eps;
    m.or_w2 = saved; 

    saved = m.or_b;
    m.or_b += eps;
    g.or_b = (costFunc(m) - c)/eps;
    m.or_b = saved; 

    saved = m.nand_w1;
    m.nand_w1 += eps;
    g.nand_w1 = (costFunc(m) - c)/eps;
    m.nand_w1 = saved; 

    saved = m.nand_w2;
    m.nand_w2 += eps;
    g.nand_w2 = (costFunc(m) - c)/eps;
    m.nand_w2 = saved; 

    saved = m.nand_b;
    m.nand_b += eps;
    g.nand_b = (costFunc(m) - c)/eps;
    m.nand_b = saved; 

    saved = m.nand_b;
    m.nand_b += eps;
    g.nand_b = (costFunc(m) - c)/eps;
    m.nand_b = saved; 

    saved = m.and_w1;
    m.and_w1 += eps;
    g.and_w1 = (costFunc(m) - c)/eps;
    m.and_w1 = saved; 

    saved = m.and_w2;
    m.and_w2 += eps;
    g.and_w2 = (costFunc(m) - c)/eps;
    m.and_w2 = saved; 

    saved = m.and_b;
    m.and_b += eps;
    g.and_b = (costFunc(m) - c)/eps;
    m.and_b = saved; 

    return g;
}

int main()
{
    Xor m = rand_xor();

    float rate = 1e-1;

    for (size_t i = 0; i < 100*1000; i++) {
        Xor g = finite_diff(m);
        m = learn(m, g, rate);
        printf("%f\n", costFunc(m));
    }

    printf("---------------------------------------------\n");
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            printf("%zu ^ %zu = %f\n", i, j, forward(m, i, j));
        } 
    }

    return 0;
}
