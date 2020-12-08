N, M = [int(i) for i in input().split()]
A = sorted([int(i) for i in input().split()])
print(min([A[i] - A[i-M+1] for i in range(M-1, N)]))
