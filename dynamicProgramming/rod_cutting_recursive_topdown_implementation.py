'''
pseudocode

Recursive top-down implementation

CUT-ROD(p, n)
    if n == 0
        return 0
    q = -infinity
    for i = 1 to n
        q = max(q, p[i] + CUT-ROD(p, n - i)
    return q

'''

import time

# dictionary of length and price
p = {1:1, 2:5, 3:8, 4:9, 5:10, 6:17, 7:17, 8:20, 9:24, 10:30}

def CUT_ROD(p, n):
    if n is 0:
        return 0

    q = float("-inf")

    for i in range(1, n + 1):
        q = max(q, p[i] + CUT_ROD(p, n - i))

    return q




if __name__ == '__main__':
    begin = time.time()
    print(CUT_ROD(p, 5))
    print("TOTAL time it takes to run {}".format(time.time() - begin))
