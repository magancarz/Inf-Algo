#include <stdio.h>
#include <string.h>

int findLargestCommonPrefixLength(const char* x, const char* y)
{
    int n = strlen(x);
    int m = strlen(y);

    int max_length = 0;
    for (int k = 0; k < n; ++k)
    {
        int valid = 1;
        int i = 0;
        for (int j = m - k - 1; j < m; ++j) 
        {
            if (x[i] != y[j]) 
            {
                valid = 0;
                break;
            }
            ++i;
        }

        if (valid)
        {
            max_length = k + 1;
        }
    }

    return max_length;
}

int main() {
    const char *x = "efcdef";
    const char *y = "wxyzef";

    int result = findLargestCommonPrefixLength(x, y);

    printf("Największa liczba k: %d\n", result);

    return 0;
}
