def solve_large(N, M):
    cur, ans, step = 0, '', 0
    if M & 1:
        step += 1
        cur += 1
        ans += 'R'

    while cur + 4*step + 4 <= M:
        cur += 4*step + 4
        step += 2
        ans += 'RR'

    while cur < M:
        cur += 2
        ans += 'LR'

    return ans


def solve_small(N, M):
    q, front = [(0, 0)], 0
    par = dict()
    while front < len(q):
        u, step = q[front]
        front += 1

        if u - step*2 - 1 >= 1 and (u - step*2 - 1, step + 1) not in par:
            par[(u - step*2 - 1, step + 1)] = (u, step)
            q.append((u - step*2 - 1, step + 1))

        if u + step*2 + 1 <= min(N, 100) and (u + step*2 + 1, step + 1) not in par:
            par[(u + step*2 + 1, step + 1)] = (u, step)
            q.append((u + step*2 + 1, step + 1))

    for i in range(100):
        if (M, i) in par:
            cur, ans = (M, i), ''
            while cur != (0, 0):
                if par[cur][0] < cur[0]:
                    ans += 'R'
                else:
                    ans += 'L'
                cur = par[cur]
            return ans[::-1]

    return ''


def main():
    N, M = [int(s) for s in input().split()]
    if M > 100:
        ans = solve_large(N, M)
    else:
        ans = solve_small(N, M)

    if ans:
        print('YES')
        print(ans)
    else:
        print('NO')

if __name__ == '__main__':
    main()
