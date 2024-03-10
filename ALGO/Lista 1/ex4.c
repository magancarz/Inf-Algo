#include <string.h>
#include <stdio.h>

int findPattern(const char* text, const char* pattern)
{
    unsigned long long text_len = strlen(text);
    unsigned long long pattern_len = strlen(pattern);

    for (unsigned long long i = 0; i < text_len - pattern_len; ++i)
    {
        if(memcmp(text + i, pattern, pattern_len))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    const char* text = "abcabcabcabcabcabcabcdef";
    const char* pattern = "def";
    printf("%d", findPattern(text, pattern));

    return 0;
}