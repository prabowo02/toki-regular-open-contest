N = int(input())
A = [int(s) for s in input().split()]
if N > 2000:
    print(0)
else:
    prod = 1
    for i in range(N):
        for j in range(i+1, N):
            prod = prod * (A[i] ^ A[j]) % 998244353
    print(prod)
