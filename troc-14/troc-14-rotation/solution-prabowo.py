n = int(input())
print(sum(sorted([int(s) for s in input().split()] + [int(s) for s in input().split()])[-n:]))
