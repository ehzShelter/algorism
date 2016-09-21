def maxF(L):
    maxlength = 0
    for k, v in L.items():
        l = len(v)
        if l > maxlength:
            maxlength = l
    return maxlength

# Your unordered list
a = [1546, 89, 989, 1131, 289, 565, 10, 2]

# pushing data to dictionary
# {0: '1546', 1: '89', 2: '989', 3: '1131', 4: '289', 5: '565', 6: '10', 7: '2'}
L = {i: str(a[i]) for i in range(len(a))}

m = maxF(L)
for k, v in L.items():
    v = (m - len(v)) * '0' + v
    L[k] = v

# python range(start, stop, step)
for x in range(m - 1, -1, -1):  # Iterating through all the digits
    bucket = {key:[] for key in range(10)}
    for k, v in L.items():
        key = int(v[x])
        bucket[key].append(v)  # Appending values in bucket using key as their digit

    i = 0
    for k, v in bucket.items():
        for e in v:
            L[i] = e  # Getting values back to list from bucket
            i += 1

# print(bucket)
# printing sorted list

V = []
print("Sorted list: ", " ", end="")
for k, v in L.items():
    # print(str(v) + " ", end="")
    V.append(str(v))


print(list((map(lambda x : int(x), V))))
