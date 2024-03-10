#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
    srand((unsigned int)time(NULL));

    int N = 10000000;
    int inside = 0;
    for (int i = 0; i < N; ++i)
    {
        double x = ((double)rand() / RAND_MAX) * M_PI;
        double y = (double)rand() / RAND_MAX;
        if (y <= sin(x))
        {
            ++inside;
        }
    }

    double ratio_inside = (double)inside / N;
    double approximated_area = ratio_inside * M_PI;
    printf("I = %f\n", approximated_area);
}
