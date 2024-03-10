#include <stdio.h>

double hornerMethod(double coefficients[], int n, double x)
{
    double result = 0;
    for (int i = 0; i < n; ++i)
    {
        result = result * x + coefficients[i];
    }
    return result;
}

int main()
{
    // 2x^4 - x^3 + 3x^2 - 2
    double coefficients[] = {2, -1, 3, 0, -2};
    int n = sizeof(coefficients) / sizeof(coefficients[0]);
    double x_value = 2;

    double result = hornerMethod(coefficients, n, x_value);
    printf("Wartosc wielomianu dla x=%lf: %lf\n", x_value, result);

    return 0;
}