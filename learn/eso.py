def esoteric_python(text):
    values = [ord(c) for c in text]

    return (
        "print(''.join(map(chr, ["
        + ",".join(map(str, values))
        + "])))"
    )


text = input("Enter text: ")
print("\nGenerated Python:\n")
print(esoteric_python(text))
