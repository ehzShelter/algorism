fib_table = {}


def fibo(n):
    fib_table[1] = 1
    fib_table[2] = 1

    for k in range(3, n + 1):
        fib_table[k] = fib_table[k - 1] + fib_table[k - 2]

    return fib_table[n]


print(fibo(5))
