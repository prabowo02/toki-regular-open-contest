# Grade using `./runner grade --solution="python3 python3-solution.py"`

n, k = [int(i) for i in input().split()]
a = sorted([int(i) for i in input().split()])

a = a[:k//2] + a[-k//2:]

ans, pre = 0, 0
for i in range(k):
    ans += a[i]*i - pre
    pre += a[i]

print(ans)
