def isalnum(string: str):
    string = string.strip()
    string = string.removeprefix('-')
    string = string.removeprefix('+')
    for char in string:
        if ord(char) >= ord('0') and ord(char) <= ord('9'):
            return 1;
        else:
            return 0;

print(isalnum('-192'))
print(isalnum("+192"))
print(isalnum("  192"))
print(isalnum("f182"))
