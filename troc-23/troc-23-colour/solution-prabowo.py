def ask(x):
    print('? {}'.format(x), flush=True)
    return int(input())


ls = [[ask(pow(2, x) * pow(3, y)) for y in range(6)] for x in range(31)]

for r1 in range(31):
    for r2 in range(r1 + 1, 31):
        for c1 in range(6):
            for c2 in range(c1 + 1, 6):
                if ls[r1][c1] == ls[r1][c2] == ls[r2][c1] == ls[r2][c2]:
                    print('! {} {}'.format(pow(2, r1) * pow(3, c2), pow(2, r2) * pow(3, c1)), flush=True)
                    exit(0)
