N, F, D = map(int, input().split())
if N < F:
    print('NO')
else:
    min_dist = F * (F + 1) // 2
    max_dist, cur_speed = 0, 0
    for i in range(N):
        if cur_speed + 1 - (N - i - 1) <= F:
            cur_speed += 1
        elif cur_speed - (N - i - 1) <= F:
            pass
        else:
            cur_speed -= 1
        max_dist += cur_speed

    if min_dist <= D <= max_dist:
        print('YES')
    else:
        print('NO')
