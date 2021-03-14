N, S, MOD = int(input()), input(), 998244353
c00, c10, s00, s10 = [[0] * (N + 2) for x in range(4)]
for i in reversed(range(N + 1)):
  c01, s01, c11, s11 = c00[:], s00[:], c10[:], s10[:]
  A, B = [0, 0] if i == N else [2, 0] if S[i] == '0' else [0, 2] if S[i] == '1' else [1, 1]
  for bal in range(N + 1):
    a, b, c, d = c01[max(bal - 1, 0)], c11[bal + 1], s11[bal + 1], max(bal - 1, 0)
    c00[bal] = bal == 0 if i == N else (A * a + B * (c01[bal + 1] + (bal == 0) * b)) % MOD
    s00[bal] = 0 if i == N else (A * (a + s01[d]) + B * (s01[bal + 1] + (bal == 0) * (b + c))) % MOD
    c10[bal] = bal >= 1 if i == N else (A * (bal >= 2) * c11[d] + B * b) % MOD
    s10[bal] = 0 if i == N else (A * (bal >= 2) * s11[d] + B * (b + c)) % MOD
print((N - (s00[0] * pow((MOD + 1) // 2, N, MOD) % MOD) + MOD) % MOD)
