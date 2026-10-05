def fact(n):
    prod = 1
    for i in range(n):
        prod *= (n - i)
    return(prod)

for i in range(10):
    print(fact(i))
