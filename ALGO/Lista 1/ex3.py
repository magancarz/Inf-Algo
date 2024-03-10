def is_postfix(string, postfix):
    return string.endswith(postfix)

string1 = "HelloWorld"
string2 = "Hello"

max_length = 0

for k in range(len(string1)):
    x_prefix = string1[:k]
    if is_postfix(string2, x_prefix):
        max_length = k

print(max_length)