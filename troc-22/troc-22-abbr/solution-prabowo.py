def solve(N, K, S, F):
    dp = [0 for _ in range(N + 1)]
    sufmax = [-10**9 for _ in range(K)]
    for i in range(1, N):
        dp[i] = dp[i - 1]
        sufmax[S[i - 1]] = max(sufmax[S[i - 1]], dp[i - 1])
        for j in range(K):
            sufmax[j] += F[S[i - 1]][S[i]]
            dp[i] = max(dp[i], sufmax[j] - F[j][S[i]])

    return dp[N - 1]


if __name__ == '__main__':
    N, K = [int(s) for s in input().split()]
    S = [int(c) - 1 for c in input()]
    F = [[int(s) for s in input().split()] for _ in range(K)]
    print(solve(N, K, S, F))
