from itertools import product

n, l, r = [int(i) for i in input().split()]
d, m = [int(i) for i in input().split()]

def count_coloring(len):
    cnt = 0
    for s in product('ABCD', repeat=len):
        ok = True
        for j in range(1, 7):
            if s[j-1] == s[j]:
                ok = False
                break

        if s[0] == s[-1]:
          ok = False

        for j in range(2, 7):
            if s[j-2] == s[j]:
                ok = False
                break

        if s[0] == s[-2] or s[1] == s[-1]:
            ok = False

        if s[0] == 'A' and s[1] == 'B' and ok:
            cnt += 1

for x in range(l, r+1):
    if x % m == d:
        ans += count_coloring(x)

print ans