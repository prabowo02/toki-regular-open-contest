n, m = [int(s) for s in input().split()]
a = sorted([int(s) for s in input().split()])
print((m - max([(a[i] - a[i - 1]) % m for i in range(n)])) % m)
