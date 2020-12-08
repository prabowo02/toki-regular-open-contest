dir = {'R': (1, 0), 'L': (-1, 0), 'U': (0, 1), 'D': (0, -1)}
print(*[sum(x) for x in zip(*[dir[c] for c in input() if c in dir])] or [0, 0])
