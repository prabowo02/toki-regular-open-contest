n, m, r = [int(s) for s in input().split()]
houses = [[int(s) for s in input().split()] for _ in range(n)]
radios = [[int(s) for s in input().split()] for _ in range(m)]

cnt, r2 = [0 for i in range(1 << m)], r**2
for x, y in houses:
    cnt[sum(1 << j for j, (a, b, _) in enumerate(radios) if (x - a)**2 + (y - b)**2 <= r2)] += 1

for i in range(m):
    for mask in range(1 << m):
        if mask >> i & 1:
            cnt[mask] += cnt[mask ^ 1 << i]

ans, mask_radios = [-1 for i in range(n + 1)], (1 << m) - 1
for mask in range(1 << m):
    cover, cost = n - cnt[~mask & mask_radios], sum(c for j, (_, _, c) in enumerate(radios) if mask >> j & 1)
    if ans[cover] == -1 or cost < ans[cover]:
        ans[cover] = cost

for i in range(n - 1, 0, -1):
    if ans[i] == -1 or ans[i + 1] != -1 and ans[i + 1] < ans[i]:
        ans[i] = ans[i+1]

print('\n'.join([str(a) for a in ans[1:]]))
