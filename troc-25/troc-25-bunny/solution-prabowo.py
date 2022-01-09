T, M = map(int, input().split())

MAXN = 200001
mobius = [1 for i in range(MAXN)]
factors = [[1] for i in range(MAXN)]

for d in range(2, MAXN):
    for j in range(d * 2, MAXN, d):
        factors[j].append(d)

    if len(factors[d]) == 1:
        # d is prime
        for j in range(d, MAXN, d):
            if j % (d * d) == 0:
                mobius[j] = 0
            else:
                mobius[j] *= -1

sums = [0 for i in range(MAXN)]
dp = [0 for i in range(MAXN)]

dp[1] = sums[1] = 1
for n in range(2, MAXN):
    dp[n] = sum(mobius[d] * sums[d] for d in factors[n]) % M

    sums[n] = dp[n]
    for d in factors[n]:
        sums[d] = (sums[d] + dp[n]) % M

print(*[dp[int(input())] for _ in range(T)], sep='\n')
