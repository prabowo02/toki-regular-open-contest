#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200000;
const int MAXM = 20;
const int MAXR = 1e9;
const int MAXCOST = 1e8;
const int MAX = 1e9;

pair<int, int> grid[1 << MAXM];

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M, R;
    vector<int> X, Y;
    vector<int> A, B, C;
    vector<int> ANS;

    void InputFormat() {
        LINE(N, M, R);
        LINES(X, Y) % SIZE(N);
        LINES(A, B, C) % SIZE(M);
    }

    void OutputFormat() {
        LINES(ANS) % SIZE(N);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= M && M <= MAXM);
        CONS(0 <= R && R <= MAXR);
        CONS(eachElementBetween(X, -MAX, MAX));
        CONS(eachElementBetween(Y, -MAX, MAX));
        CONS(eachElementBetween(A, -MAX, MAX));
        CONS(eachElementBetween(B, -MAX, MAX));
        CONS(eachElementBetween(C, 0, MAXCOST));
    }

    void Subtask1() {
        Points(100);
    }

private:
    bool eachElementBetween(const vector<int> &vec, int l, int r) {
        for (auto &x : vec) {
            if (x < l || r < x) return false;
        }

        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "4 2 4",
            "1 1",
            "2 2",
            "3 3",
            "4 4",
            "0 0 1",
            "4 2 100",
        });

        Output({
            "1",
            "1",
            "100",
            "100",
        });
    }
    
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "3 1 0",
            "2 2",
            "1 1",
            "-1 -1",
            "2 2 0",
        });

        Output({
            "0",
            "-1",
            "-1",
        });
    }

    void SampleTestCase3() {
        Subtasks({1});
        Input({
            "4 3 1",
            "-2 0",
            "0 0",
            "1 1",
            "100 100",
            "-1 0 1",
            "1 0 1",
            "50 -50 0",
        });

        Output({
            "1",
            "1",
            "2",
            "-1",
        });
    }

    void BeforeTestCase() {
        X.clear();
        Y.clear();
        A.clear();
        B.clear();
        C.clear();
    }

    void AfterTestCase() {

    }

    void TestGroup1() {
        Subtasks({1});

        // All answers: -1
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(10, 1000), noAnswer()); 

        // R = 0
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = rnd.nextInt(5, MAXM), R = 0, caseR_0());
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = rnd.nextInt(15, MAXM), R = 0, caseR_0());

        // Extreme Points + Max Radius
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = rnd.nextInt(5, MAXM), R = MAXR, cornerPoints());
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = rnd.nextInt(15, MAXM), R = MAXR, cornerPoints()); 

        // Must build all radio with max cost
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = MAXM, R = rnd.nextInt(100000, 1000000), maximumCost());

        // All answers
        CASE(N = rnd.nextInt(20000, MAXN / 4), M = rnd.nextInt(15, MAXM), R = rnd.nextInt(10000000, MAXR), allAnswers());

        // Max-test [with some has previous defined property]
        // 1) R = 0
        CASE(N = MAXN, M = MAXM, R = 0, caseR_0());

        // 2) MITM Killer
        CASE(N = MAXN, M = MAXM, clustered(9, 11));
        CASE(N = MAXN, M = MAXM, clustered(9, 11));
        CASE(N = MAXN, M = MAXM, clustered(9, 11));
        CASE(N = MAXN, M = MAXM, clustered(10, 10));

        // 3) Clustered
        CASE(N = MAXN, M = MAXM, clustered(0, 20));
        CASE(N = MAXN, M = MAXM, clustered(11, 20));

        // 4) Randomized
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(100000000, MAXR), randomPoints());
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(100000000, MAXR), randomPoints());

        // 5) Same Point
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(100000000, MAXR), allSame());

        // 6) Distinct Answers
        CASE(N = (1 << 17) - 1, M = 17, R = rnd.nextInt(100000, 1000000), distinctAnswers());

        // Many distinct masks
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(1000, 2000), distinctMasks());
        CASE(N = MAXN, M = MAXM, R = rnd.nextInt(1000, 2000), distinctMasks());
    }

private:
    void initialize() {
        X.resize(N);
        Y.resize(N);
        A.resize(M);
        B.resize(M);
        C.resize(M);
    }
    
    int adjust(long long x) {
        return min(max(-1LL * MAX, x), 1LL * MAX);
    }

    int sign(int x) {
        return x > 0 ? 1 : -1;
    }

    long long square(long long x) {
        return x * x;
    }

    bool inRadius(int x, int y) {
        for (int i = 0; i < M; i++) {
            if (square(x - A[i]) + square(y - B[i]) <= square(R)) return true;
        }
        return false;
    }

    void distinctMasks() {
        initialize();

        for (int i = 0; i < (1 << M); i++) grid[i] = make_pair(MAX + 1, MAX + 1);

        int r = R - 10;
        const long double pi = acosl(-1.0);

        for (int i = 0; i < M; i++) {
            C[i] = rnd.nextInt(0, MAXCOST);

            A[i] = r * cosl(2 * pi * i / M);
            B[i] = r * sinl(2 * pi * i / M);
        }

        const int mn = - (R << 2);
        const int mx = R << 2;

        for (int i = mn; i <= mx; i++) {
            for (int j = mn; j <= mx; j++) {
                int mask = 0;
                for (int k = 0; k < M; k++) {
                    if (square(i - A[k]) + square(j - B[k]) <= square(R)) mask |= 1 << k;
                }

                grid[mask] = make_pair(i, j);
            }
        }

        int cnt = 1 << M;
        --cnt;

        for (int i = 0; i < N; i++) {
            while (cnt >= 0 && grid[cnt].first == MAX + 1) cnt--;

            if (cnt < 0) {
                int dice = rnd.nextInt(i);

                X[i] = X[dice];
                Y[i] = Y[dice];
            } else {
                tie(X[i], Y[i]) = grid[cnt--];
            }
        }

        // Scale all by 1000
        const int c = 1000;
        R *= c;

        for (int i = 0; i < M; i++) {
            A[i] *= c; B[i] *= c;
        }

        for (int i = 0; i < N; i++) {
            X[i] *= c; Y[i] *= c;
        }
    }

    void noAnswer() {
        initialize();

        // Generate radio points
        for (int i = 0; i < M; i++) {
            A[i] = rnd.nextInt(-MAX, MAX);
            B[i] = rnd.nextInt(-MAX, MAX);
            C[i] = rnd.nextInt(0, MAXCOST);
        }

        // Generate houses points, none of them inside the radius of any radio
        for (int i = 0; i < N; i++) {
            do {
                X[i] = rnd.nextInt(-MAX, MAX);
                Y[i] = rnd.nextInt(-MAX, MAX);
            } while (inRadius(X[i], Y[i]));
        }
    }

    void caseR_0() {
        initialize();

        // Generate radio points
        for (int i = 0; i < M; i++) {
            A[i] = rnd.nextInt(-MAX, MAX);
            B[i] = rnd.nextInt(-MAX, MAX);
            C[i] = rnd.nextInt(0, MAXCOST);
        }
        
        // Generate houses points
        for (int i = 0; i < N; i++) {
            if (rnd.nextInt(0, 3) <= 2) {
                // Inside circle
                int idx = rnd.nextInt(0, M - 1);

                X[i] = A[idx];
                Y[i] = B[idx];
            } else {
                // Pick random point

                X[i] = rnd.nextInt(-MAX, MAX);
                Y[i] = rnd.nextInt(-MAX, MAX);
            }
        }
    }

    void cornerPoints() {
        initialize();

        // Generate radio points
        vector<pair<int, int> > coord = {{MAX, MAX}, {MAX, -MAX}, {-MAX, MAX}, {-MAX, -MAX}};
        for (int i = 0; i < M; i++) {
            int dice = rnd.nextInt(0, 3);

            tie(A[i], B[i]) = coord[dice];
            A[i] += -sign(A[i]) * rnd.nextInt(0, 1000);
            B[i] += -sign(B[i]) * rnd.nextInt(0, 1000);
            C[i] = rnd.nextInt(0, MAXCOST);
        }

        for (int i = 0; i < N; i++) {
            int dice = rnd.nextInt(0, 3);

            tie(X[i], Y[i]) = coord[dice];
            X[i] += -sign(X[i]) * rnd.nextInt(0, 1000);
            Y[i] += -sign(Y[i]) * rnd.nextInt(0, 1000);
        }
    }

    void maximumCost() {
        initialize();

        // Any radio must not be contained inside radius of another radio
        for (int i = 0; i < M; i++) {
            C[i] = MAXCOST;

            while(true) {
                bool inside = false;

                A[i] = rnd.nextInt(-MAX, MAX), B[i] = rnd.nextInt(-MAX, MAX);
                for (int j = 0; j < i; j++) {
                    if (square(A[i] - A[j]) + square(B[i] - B[j]) <= square(R)) {
                        inside = true;
                        break;
                    }
                }

                if (inside) continue;

                break;
            }
        }

        for (int i = 0; i < min(N, M); i++) {
            X[i] = A[i];
            Y[i] = B[i];
        }

        for (int i = M; i < N; i++) {
            int dice = rnd.nextInt(0, M - 1);

            X[i] = adjust(1LL * A[dice] + rnd.nextInt(- (R << 1), R << 1));
            Y[i] = adjust(1LL * B[dice] + rnd.nextInt(- (R << 1), R << 1));
        }
    }

    void allAnswers() {
        initialize();
        const int inSquare = floor(R / sqrt(2));

        // Generate radio points
        for (int i = 0; i < M; i++) {
            A[i] = rnd.nextInt(-MAX, MAX);
            B[i] = rnd.nextInt(-MAX, MAX);
            C[i] = rnd.nextInt(0, MAXCOST);
        }

        // Generate houses points, all of them inside the radius of at least one radio
        for (int i = 0; i < N; i++) {
            int dice = rnd.nextInt(0, M - 1);

            X[i] = A[dice] + rnd.nextInt(-inSquare, inSquare);
            Y[i] = B[dice] + rnd.nextInt(-inSquare, inSquare);

            X[i] = adjust(X[i]);
            Y[i] = adjust(Y[i]);
        }
    }

    void clustered(int l, int r) {
        R = rnd.nextInt(300, 400);
        vector<pair<int, int> > grid[21];
        initialize();
        
        for (int i = 0; i < M; i++) {
            A[i] = rnd.nextInt(-20, 20);
            B[i] = rnd.nextInt(-20, 20);
            C[i] = rnd.nextInt(0, MAXCOST);
        }

        const int mn = -20 - R;
        const int mx = 20 + R;

        for (int i = mn; i <= mx; i++) {
            for (int j = mn; j <= mx; j++) {
                int cnt = 0;
                for (int k = 0; k < M; k++) {
                    if (square(i - A[k]) + square(j - B[k]) <= square(R)) cnt++;
                }

                grid[cnt].emplace_back(i, j);
            }
        }

        for (int i = 0; i < N; i++) {
            int dice = rnd.nextInt(l, r);

            tie(X[i], Y[i]) = grid[dice][rnd.nextInt(grid[dice].size())];
        }

        // Scale all by 1000
        const int c = 1000;
        R *= c;

        for (int i = 0; i < M; i++) {
            A[i] *= c; B[i] *= c;
        }

        for (int i = 0; i < N; i++) {
            X[i] *= c; Y[i] *= c;
        }
    }

    void randomPoints() {
        initialize();
        
        // Generate radio points
        for (int i = 0; i < M; i++) {
            A[i] = rnd.nextInt(-MAX, MAX);
            B[i] = rnd.nextInt(-MAX, MAX);
            C[i] = rnd.nextInt(0, MAXCOST);
        }

        // Generate houses points
        for (int i = 0; i < N; i++) {
            int dice = rnd.nextInt(0, M - 1);

            X[i] = adjust(1LL * A[dice] + rnd.nextInt(- (R << 1), R << 1));
            Y[i] = adjust(1LL * B[dice] + rnd.nextInt(- (R << 1), R << 1));
        }
    }

    void allSame() {
        initialize();

        const int inSquare = floor(R / sqrt(2));

        A[0] = rnd.nextInt(-MAX, MAX);
        B[0] = rnd.nextInt(-MAX, MAX);
        C[0] = rnd.nextInt(0, MAXCOST);

        X[0] = adjust(1LL * A[0] + rnd.nextInt(-inSquare, inSquare));
        Y[0] = adjust(1LL * B[0] + rnd.nextInt(-inSquare, inSquare));

        for (int i = 1; i < N; i++) {
            X[i] = X[0];
            Y[i] = Y[0];
        }

        for (int i = 1; i < M; i++) {
            A[i] = A[0];
            B[i] = B[0];
            C[i] = rnd.nextInt(0, MAXCOST);
        }
    }

    void distinctAnswers() {
        initialize();

        for (int i = 0; i < M; i++) {
            C[i] = 1 << i;

            while (true) {
                bool disjoint = true;
                A[i] = rnd.nextInt(-MAX, MAX);
                B[i] = rnd.nextInt(-MAX, MAX);

                for (int j = 0; j < i; j++) {
                    if (square(A[i] - A[j]) + square(B[i] - B[j]) <= square(R << 1)) {disjoint = false; break;}
                }

                if (disjoint) break;
            }
        }

        int bit = 0;
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (cnt == (1 << bit)) bit++, cnt = 0;

            X[i] = A[bit];
            Y[i] = B[bit];
            cnt++;
        }
    }
};