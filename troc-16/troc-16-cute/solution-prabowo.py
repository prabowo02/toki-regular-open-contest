n, m, mod = [int(s) for s in input().split()] + [10**9 + 7]
a, b = 1, m
for i in range(1, n):
    a, b = b, (a + b) * (m - 1) % mod

print((b - pow(m - 1, n, mod)) % mod)
