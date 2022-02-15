import bisect
import heapq


def solve(X, Y, bees, flowers):
    lftBees = sorted([bee[0] for bee in bees if bee[1] == 1])
    rgtBees = sorted([bee[0] for bee in bees if bee[1] == -1])

    timeFlower = []
    for flower in flowers:
        nearestLft = bisect.bisect_right(lftBees, flower[0]) - 1
        nearestRgt = bisect.bisect_left(rgtBees, flower[0])

        t = 10**9
        if nearestLft >= 0:
            t = min(t, flower[0] - lftBees[nearestLft])
        if nearestRgt < len(rgtBees):
            t = min(t, rgtBees[nearestRgt] - flower[0])

        timeFlower.append((t, flower[1]))

    timeFlower.sort(reverse=True)

    pq, ans = [], 0
    for t in range(Y, X):
        while timeFlower and timeFlower[-1][0] <= t:
            heapq.heappush(pq, timeFlower.pop()[1])

        if not pq:
            return -1

        ans += heapq.heappop(pq)

    return ans


if __name__ == '__main__':
    X, Y = [int(s) for s in input().split()]
    N = int(input())
    bees = [[int(s) for s in input().split()] for _ in range(N)]
    M = int(input())
    flowers = [[int(s) for s in input().split()] for _ in range(M)]
    print(solve(X, Y, bees, flowers))
