#include <stdio.h>
#include <string.h>

void rabinKarpSearch(char pattern[], char text[])
{
    int pattern_length = strlen(pattern);
    int text_length = strlen(text);
    int base = 256;
    int prime = 101;

    int pattern_hash = 0;
    int text_hash = 0;
    int h = 1;

    for (int i = 0; i < pattern_length - 1; ++i)
    {
        h = (h * base) % prime;
    }

    for (int i = 0; i < pattern_length; ++i)
    {
        pattern_hash = (base * pattern_hash + pattern[i]) % prime;
        text_hash = (base * text_hash + text[i]) % prime;
    }

    for (int i = 0; i <= text_length - pattern_length; ++i)
    {
        if (pattern_hash == text_hash)
        {
            printf("Pattern found at index %d\n", i);
        }

        if (i < text_length - pattern_length)
        {
            text_hash = (base * (text_hash - text[i] * h) + text[i + pattern_length]) % prime;

            if (text_hash < 0)
            {
                text_hash += prime;
            }
        }
    }
}

int main() {
    char text[] = "ababcababcabcabc";
    char pattern[] = "abc";

    rabinKarpSearch(pattern, text);

    return 0;
}
