def ask(x):
    print('? {}'.format(x), flush=True)
    return int(input())


def search(l, r, bit):
    ans = None
    while l <= r:
        mid = (l + r) // 2
        if ask(mid) == bit:
            ans, l = mid, mid + 1
        else:
            r = mid - 1
    return ans


def solve(N):
    first = ask(1)
    current = 1
    while True:
        current *= 2
        if ask(current) != first:
            one = search(current // 2, current, first)
            break

    current = one + 1
    while True:
        current *= 2
        if ask(current) == first:
            two = search(current // 2, current, 1 - first)
            break

    x = two - one
    a = x - one if first == 0 else x * 2 - one
    y = (N + a + x*2 - 1) // (x*2)
    b = 2*x*y - a - N

    return x, y, a, b


if __name__ == '__main__':
    print(*solve(int(input())))
