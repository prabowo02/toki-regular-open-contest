import sys

memo = dict()
N = int(input())


def query(i):
    if memo.get(i) == None:
        sys.stdout.write("? {}\n".format(i))
        sys.stdout.flush()
        memo[i] = int(input())
    return memo[i]


def binarySearch(l, r):
    lo, hi = l, r
    while lo < hi:
        md = (lo + hi) // 2
        if query(l) == query(md):
            lo = md + 1
        else:
            hi = md
    return lo


pw = 1
while query(1) == query(pw):
    pw *= 2

firstChange = binarySearch(1, pw)

pw //= 2
while query(firstChange) == query(firstChange + pw - 1):
    pw *= 2

secondChange = binarySearch(firstChange, firstChange + pw - 1)

x = secondChange - firstChange
a = 2 * x - (firstChange - 1) - query(firstChange) * x
b = -(a + N) % (2 * x)
y = (N + a + b) // (2 * x)

sys.stdout.write("! {} {} {} {}\n".format(x, y, a, b))
sys.stdout.flush()
