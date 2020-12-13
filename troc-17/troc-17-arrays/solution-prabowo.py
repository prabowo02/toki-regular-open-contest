LG = 30
MOD = 998244353

n = int(input())
lst = [-1 for i in range(LG)]

ans = 1
for i, a in enumerate([int(s) for s in input().split()]):
    v = []
    for j in range(LG - 1, -1, -1):
        if a >> j & 1:
            lst[j] = i
        v.append((lst[j], j))
    v.sort(reverse=True)

    idx, cur = i, 0
    for l, j in v:
        ans = ans * pow(cur, idx - l, MOD) % MOD
        cur |= 1 << j
        idx = l

    ans = ans * pow(cur, idx + 1, MOD) % MOD

print(ans)
