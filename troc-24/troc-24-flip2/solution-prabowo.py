N = int(input())
A = [int(s) for s in input().split()]
print(abs(sum(A[::2]) - sum(A[1::2])) if N > 2 else A[0] - A[1])
