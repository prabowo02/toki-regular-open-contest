N, K = [int(x) for x in input().split()]
S = [int(x) - 1 for x in input()]
f = [[int(x) for x in input().split()] for _ in range(K)]

dp = [0 if _ == S[0] else int(1e18) for _ in range(K)]
for a in S[1:-1:]:
    dp[a] = min(dp[a], dp[a] + f[a][a])
    for b in range(K):
        if a != b:
            dp[a] = min(dp[a], dp[b] + f[b][a])

print(sum([f[S[i]][S[i + 1]] for i in range(N - 1)]) -
      min([dp[i] + f[i][S[-1]] for i in range(K)]))
