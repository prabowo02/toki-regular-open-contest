def main():
    N, Q = [int(s) for s in input().split()]
    pos = dict()
    for i in range(N):
        pos[(i, 0)] = -i

    pref = [0 for _ in range(N + 1)]

    def add(p, t):
        if t > N - p:
            t = N - p
        pref[0] += 1
        pref[p] += 1
        pref[t] -= 1
        pref[p + t] -= 1


    head = (0, 0)
    dxs, dys = (0, 1, 0, -1), (1, 0, -1, 0)
    for t, m in enumerate(input()):
        if m == 'U':
            head = (head[0], head[1] + 1)
        elif m == 'D':
            head = (head[0], head[1] - 1)
        elif m == 'R':
            head = (head[0] + 1, head[1])
        elif m == 'L':
            head = (head[0] - 1, head[1])

        for dx, dy in zip(dxs, dys):
            side = pos.get((head[0] + dx, head[1] + dy))
            if side is not None and side > t - N + 1:
                add(t - side + 1, N if side == t else Q - t)

        pos[head] = t + 1

    s = 0
    for p in pref[:N]:
        s += p
        print(s)


if __name__ == '__main__':
    main()
