N, M, K = map(int, input().split())
A = [int(s) for s in input().split()]
B = [int(s) for s in input().split()]

def maxmin(A, K):
    cur = maxi = mini = sum(A[:K])
    for i in range(K, len(A)):
        cur = cur - A[i - K] + A[i]
        maxi = max(maxi, cur)
        mini = min(mini, cur)
    return maxi, mini


def count(x, y):
    return x * (K - y) + (K - x) * y

(A0, A1), (B0, B1) = maxmin(A, K), maxmin(B, K)

print(max(count(A0, B0), count(A0, B1), count(A1, B0), count(A1, B1)))
