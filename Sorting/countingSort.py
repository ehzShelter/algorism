A = [11, 1, 4, 3, 5, 0, 2, 15, 3, 3, 7, 6, 8, 9, 8]

K = max(A) + 1

L = [[] for i in range(K)]

n = len(A)

for j in range(n):
    L[(A[j])].append(A[j])

output = []
for i in range(K):
    output.extend(L[i])

print(output)
