MOD = 998244353

n, k = [int(s) for s in input().split()]
fixed = [False for i in range(n + 1)]
for _ in range(k):
    fixed[int(input().split()[1])] = True

dp = [[1 for i in range(n + 1)]]
for i in range(1, n + 1):
    dp.append([0 for i in range(n + 1)])
    for delta in range(i, n + 1):
        if fixed[i]:
            dp[i][delta] = dp[i - 1][delta - 1]
        else:
            dp[i][delta] = ((dp[i - 1][delta] - dp[i - 1][delta - 1]) * (delta - i + 1) + dp[i - 1][delta - 1])
        dp[i][delta] = (dp[i][delta] + dp[i][delta - 1]) % MOD

print((dp[n][n] - dp[n][n - 1]) % MOD)
