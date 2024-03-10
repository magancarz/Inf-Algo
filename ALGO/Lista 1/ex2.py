def is_prefix(string, prefix):
    return string.startswith(prefix)

def is_postfix(string, postfix):
    return string.endswith(postfix)

string1 = "HelloWorld"
string2 = "Hello"
string3 = "World"

if is_prefix(string1, string2):
    print(f"{string2} jest prefixem {string1}")
else:
    print(f"{string2} nie jest prefixem {string1}")

if is_postfix(string1, string3):
    print(f"{string3} jest postfixem {string1}")
else:
    print(f"{string3} nie jest postfixem {string1}")