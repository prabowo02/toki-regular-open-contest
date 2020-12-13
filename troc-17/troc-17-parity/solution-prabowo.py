N = int(input())
A = [int(s) for s in input().split()]
B = [int(s) for s in input().split()]
print(sum(a**b for a, b in zip(A, B)) & 1)
