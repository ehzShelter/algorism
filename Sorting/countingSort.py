A = [1, 4, 5, 7, 6, 8, 9, 8]

K = 10
L = [[] for i in range(K)]

n = 8
for j in range(n):
    L[(A[j])].append(A[j])


output = []
for i in range(K):
    output.extend(L[i])

print(output)
