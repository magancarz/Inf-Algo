#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPrefix(const char* str, const char* prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool isPostfix(const char* str, const char* postfix)
{
    size_t str_len = strlen(str);
    size_t postfix_len = strlen(postfix);

    if (str_len < postfix_len)
    {
        return false;
    }

    return strncmp(str + (str_len - postfix_len), postfix, postfix_len) == 0;
}

int main()
{
    const char* string1 = "HelloWorld";
    const char* string2 = "Hello";
    const char* string3 = "World";

    if (isPrefix(string1, string2))
    {
        printf("%s jest prefixem %s\n", string2, string1);
    }
    else
    {
        printf("%s nie jest prefixem %s\n", string2, string1);
    }

    if (isPostfix(string1, string3))
    {
        printf("%s jest postfixem %s\n", string3, string1);
    }
    else
    {
        printf("%s nie jest postfixem %s\n", string3, string1);
    }

    return 0;
}