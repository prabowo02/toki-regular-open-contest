sides, getArea = [int(i) for i in input().split()], lambda n: n * (n+1) // 2
print(getArea(sum(sides[:3]) - 2) - sum([getArea(x-1) for x in sides[::2]]))
