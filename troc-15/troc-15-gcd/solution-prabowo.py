from math import gcd

g, l = [int(s) for s in input().split()]
if l % g:
    print(-1, -1)
    exit(0)

l //= g
i, ans = 1, (-1, -1)
while i*i <= l:
    if l % i == 0 and gcd(i, l // i) == 1 and (ans[0] == -1 or g*(i + l//i) < ans[0] + ans[1]):
        ans = (g * i, g * l // i)
    i += 1

print(*ans)
