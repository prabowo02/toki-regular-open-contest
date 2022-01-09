MOD = 998244353

N, K = map(int, input().split())
A = [0] + [int(s) for s in input().split()]

lft = [i for i in range(N + 1)]
rgt = [i for i in range(N + 1)]

for i in range(1, N + 1):
    while lft[i] > 1 and A[lft[i] - 1] <= A[i]:
        lft[i] -= 1
    while rgt[i] < N and A[rgt[i] + 1] <= A[i]:
        rgt[i] += 1

dp0 = [[1 if i >= j else 0 for j in range(N + 1)] for i in range(N + 1)]
dp1 = [[0 for _ in range(N + 1)] for i in range(N + 1)]

ans = 1
for k in range(K):
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            dp1[i][j] = 0
            if lft[i] <= j <= rgt[i]:
                dp1[i][j] = (dp0[i - 1][j - 1] + dp1[i][j - 1]) % MOD
    dp0[0][0] = 0
    for i in range(1, N + 1):
        dp0[i][0] = 0
        for j in range(1, N + 1):
            if i == j:
                dp0[i][j] = (dp0[i - 1][j - 1] + dp1[i][j - 1] + dp0[i - 1][j]) % MOD
            else:
                dp0[i][j] = (dp1[i][j] + dp0[i - 1][j]) % MOD

    ans = (ans + dp0[N][N]) % MOD

print(ans)
