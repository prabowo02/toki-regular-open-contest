N, M, MOD = [int(s) for s in input().split()] + [10**9 + 7]
print(((M - 1) * pow(M, N - 1, MOD) + M) % MOD)
