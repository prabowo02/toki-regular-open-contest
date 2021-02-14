MOD = 998244353

N, M, A, B, C = [int(x) for x in input().split()]

div_2 = (MOD + 1) // 2
choose = [[0 for j in range(max(N, M) + 1)] for i in range(max(N, M) + 1)]

cnt = [[[0 for k in range(M + 1)] for j in range(N + 1)] for i in range(min(N, M) + 6)]
scr = [[[0 for k in range(M + 1)] for j in range(N + 1)] for i in range(min(N, M) + 6)]

for n in range(max(N, M) + 1):
  choose[n][0] = 1
  for m in range(1, n + 1):
    choose[n][m] = choose[n - 1][m] + choose[n - 1][m - 1]
    choose[n][m] %= MOD

cnt[0][1][0] = 1
cnt[4][0][0] = 1
cnt[5][0][0] = 1

for n in range(1, N + 1):
  for m in range(n - 1, M + 1):
    if m > 0:
      cnt[0][n][m] = (cnt[0][n][m - 1] * n * (n + 1) * div_2 + cnt[2][n][m - 1] * div_2) % MOD
      scr[0][n][m] = (cnt[0][n][m - 1] * n * (n + 1) * div_2 * (B - A) + scr[0][n][m - 1] * n * (n + 1) * div_2 + cnt[2][n][m - 1] * div_2 * (C - A) + scr[2][n][m - 1] * div_2) % MOD

      cnt[1][n][m] = m * (cnt[2][n][m - 1] + cnt[0][n][m - 1] * n * n) % MOD
      scr[1][n][m] = m * (scr[2][n][m - 1] + scr[0][n][m - 1] * n * n) % MOD

    for node in range(1, n + 1):
      for edge in range(node - 1, m + 1):
        ways = choose[n][node] * choose[m][edge] * node * node % MOD
        cnt[2][n][m] += ways * cnt[0][node][edge] * cnt[1][n - node][m - edge]
        scr[2][n][m] += ways * scr[0][node][edge] * cnt[1][n - node][m - edge] + ways * cnt[0][node][edge] * scr[1][n - node][m - edge]
        cnt[2][n][m] %= MOD
        scr[2][n][m] %= MOD

    for node in range(1, n + 1):
      for edge in range(node - 1, m):
        ways = choose[n - 1][node - 1] * choose[m][edge] * node * (m - edge) % MOD
        for child in range(1, min(n - node + 2, m - edge + 1)):
          cnt[5 + child][n][m] += ways * cnt[3][node][edge] * cnt[5 + child - 1][n - node][m - 1 - edge]
          scr[5 + child][n][m] += ways * cnt[3][node][edge] * scr[5 + child - 1][n - node][m - 1 - edge] + ways * scr[3][node][edge] * cnt[5 + child - 1][n - node][m - 1 - edge]
          cnt[5 + child][n][m] %= MOD
          scr[5 + child][n][m] %= MOD

    for node in range(1, n + 1):
      for edge in range(node - 1, m + 1):
        ways = choose[n - 1][node - 1] * choose[m][edge]
        for child in range(0, min(n - node + 1, m - edge + 1)):
          cnt[3][n][m] += ways * cnt[0][node][edge] * cnt[5 + child][n - node][m - edge]
          scr[3][n][m] += ways * cnt[0][node][edge] * scr[5 + child][n - node][m - edge] + ways * scr[0][node][edge] * cnt[5 + child][n - node][m - edge]
          cnt[3][n][m] %= MOD
          scr[3][n][m] %= MOD
          ways = ways * node % MOD

  for m in range(0, M + 1):
    for node in range(1, n + 1):
      for edge in range(node - 1, m + 1):
        ways = choose[n - 1][node - 1] * choose[m][edge]
        cnt[4][n][m] += ways * cnt[3][node][edge] * cnt[4][n - node][m - edge]
        scr[4][n][m] += ways * cnt[3][node][edge] * scr[4][n - node][m - edge] + ways * scr[3][node][edge] * cnt[4][n - node][m - edge]
        cnt[4][n][m] %= MOD
        scr[4][n][m] %= MOD

print((scr[4][N][M] * pow(cnt[4][N][M], MOD - 2, MOD) + M * A) % MOD)
