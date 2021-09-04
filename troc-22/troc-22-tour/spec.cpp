#include <tcframe/spec.hpp>
#include <iostream>
#include <assert.h>

#define vi vector<int>
#define ll long long
#define pii pair<int, int>
#define fst first
#define snd second
using namespace tcframe;
const ll MAX_N = 100000, MAX_D = 10000, MAX_C = 1e12;

using namespace std;

// IMPORTANT NOTE: Increase stack limit, as this code uses DFS as a sub-routine.

class ProblemSpec : public BaseProblemSpec 
{
protected:
    int N; ll C;
   	vector<int> P, D;
    ll ans;

    void InputFormat() 
    {
        LINE(N, C);
        LINES(P, D) % SIZE(N - 1);
    }

    void OutputFormat() 
    {
        LINE(ans);
    }

    void GradingConfig() 
    {
        TimeLimit(2);
        MemoryLimit(128);
    }

    void Constraints() 
    {
        CONS(1 <= N && N <= MAX_N);
        CONS(1 <= C && C <= MAX_C);
        CONS(checkArray(D, 1, MAX_D));
        CONS(checkPar(P));
    }

    void Subtask1() 
    {
        Points(100);
    }

private:
    bool checkArray(const vi& V, int l, int r)
    {
        for (int i = 0; i < V.size(); i++)
        {
            if (V[i] < l || V[i] > r) return 0;
        }
        return 1;
    }

    bool checkPar(const vi& V)
    {
        for (int i = 0; i < V.size(); i++)
        {
            if (V[i] < 1 || V[i] > i + 1) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> 
{
protected:
    void SampleTestCase1() 
    {
        Subtasks({1});
        Input({
            "6 7",
            "1 2",
            "1 1",
            "3 2",
            "3 1",
            "5 1"
        });
        Output({
            "29"
        });
    }

    void SampleTestCase2() 
    {
        Subtasks({1});
        Input({
            "5 20",
            "1 5",
            "1 5",
            "3 10",
            "3 5"
        });
        Output({
            "100"
        });
    }

    void SampleTestCase3()
    {
        Subtasks({1});
        Input({
            "14 79",
            "1 5",
            "1 2",
            "1 8",
            "2 1",
            "2 3",
            "3 4",
            "3 1",
            "3 9",
            "4 6",
            "5 5",
            "7 3",
            "7 8",
            "10 1"
        });
        Output({
            "654"
        });
    }

    void BeforeTestCase() 
    {
        P.clear();
        D.clear();
    }

    void AfterTestCase()    // Shuffling nodes, fixes tree indexing for input.
    {
        vector<int> ID;
        int cnt = 0;
        vector<vector<pii>> adj;

        for (int i = 0; i < N; i++) {ID.push_back(i); adj.push_back(vector<pii>());}
        rnd.shuffle(ID.begin() + 1, ID.end());
        
        for (int i = 1; i < N; i++)
        {
            adj[ID[i]].push_back({ID[P[i - 1]], D[i - 1]});
            adj[ID[P[i - 1]]].push_back({ID[i], D[i - 1]});
        }

        DFS(adj, cnt, 0, -1);
        for (int i = 0; i + 1 < N; i++) P[i]++;
    }

    void TestGroup1()
    {
        Subtasks({1});

        // Manual cases (3)
        CASE(N = 1, C = rnd.nextLongLong(1, MAX_C), P = {}, D = {});                                                        // Dot graph.
        CASE(N = 2, C = 5, P = {0}, D = {2});                                                                               // N = 2, one set.
        CASE(N = 2, C = 35, P = {0}, D = {6});                                                                              // N = 2, two sets.

        // Line tree (6)
        CASE(N = MAX_N, C = MAX_C, P = LineTree(N), D = RandomD(N, MAX_D, MAX_D));                                          // Max output
        CASE(N = MAX_N, C = 6941 * 6941, P = LineTree(N), D = RandomD(N, 6941, 6941));                                      // Maximum N, Forces maximum size CHT
        CASE(N = MAX_N, C = rnd.nextLongLong(500 * 499, 500 * 501), P = LineTree(N), D = RandomD(N, 1, 1000));              // Maximum N, High density CHT (~0.75N)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = LineTree(N), D = RandomD(N, 1, MAX_D));                         // Maximum N, Random
        CASE(N = MAX_N, C = rnd.nextLongLong(MAX_C / 5 * 3, MAX_C), P = LineTree(N), D = RandomD(N, 1, MAX_D));             // Maximum N, High number of chains.                     
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(1, MAX_C), P = LineTree(N), D = RandomD(N, 1, MAX_D));         // Random

        // Star tree (3)
        CASE(N = MAX_N, C = rnd.nextLongLong(MAX_C / 100, MAX_C), P = StarTree(N), D = RandomD(N, 1, 1000));                // Each set has exactly one node.
        CASE(N = MAX_N, C = rnd.nextLongLong(1, 1000000), P = StarTree(N), D = RandomD(N, MAX_D / 10, MAX_D));              // One set has two nodes.
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(1, MAX_C), P = StarTree(N), D = RandomD(N, 1, MAX_D));         // Random

        // Broom tree (4)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = BroomTree(N, rnd.nextInt(1, 10)), D = RandomD(N, 1, MAX_D));                                 // Short broom "stick"       
        CASE(N = MAX_N, C = rnd.nextLongLong(5000 * 4999, 5000 * 5001), P = BroomTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));      // Maximum N, High density CHT (~0.64N)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = BroomTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));                      // Maximum N, Random                   
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(1, MAX_C), P = BroomTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));      // Random

        // Binary tree (5)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = BinaryTree(N), D = RandomD(N, 1, MAX_D));                       // Maximum N, Random
        CASE(N = MAX_N, C = 10, P = BinaryTree(N), D = RandomD(N, 1, MAX_D));                                               // High density CHT (~0.3N), all nodes are (most likely) in seperate chains.
        CASE(N = MAX_N, C = rnd.nextLongLong(MAX_C / 10, MAX_C), P = BinaryTree(N), D = RandomD(N, 1, MAX_D));              // low number of chains.
        CASE(N = MAX_N, C = rnd.nextLongLong(1, 100), P = BinaryTree(N), D = RandomD(N, 1, MAX_D));                         // high number of chains 
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(0, MAX_C), P = BinaryTree(N), D = RandomD(N, 1, MAX_D));       // Random

        // Caterpillar tree (4)
        CASE(N = MAX_N, C = 7192 * 7192, P = CatTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 7192, 7192));                                   // Maximum N, High density CHT (~0.73N)
        CASE(N = MAX_N, C = rnd.nextLongLong(5000 * 4999, 5000 * 5001), P = CatTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));      // Maximum N, High density CHT (~0.64N)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = CatTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));                      // Maximum N, Random                   
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(1, MAX_C), P = CatTree(N, rnd.nextInt(N / 4, N / 4 * 3)), D = RandomD(N, 1, MAX_D));      // Random

        // Large-degree tree (3)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = LDTree(N, rnd.nextInt(N / 10, N / 4)), D = RandomD(N, 1, MAX_D));                // Maximum N, Random
        CASE(N = MAX_N, C = rnd.nextLongLong(MAX_C / 10, MAX_C), P = LDTree(N, rnd.nextInt(N / 10, N / 4)), D = RandomD(N, 1, MAX_D));       // low number of chains.
        CASE(N = MAX_N, C = rnd.nextLongLong(1, 100), P = LDTree(N, rnd.nextInt(N / 10, N / 4)), D = RandomD(N, 1, MAX_D));                      // high number of chains 

        // Random tree (7)
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = RandomTree(N), D = RandomD(N, 1, MAX_D));                       // Maximum N, Random
        CASE(N = MAX_N, C = rnd.nextLongLong(1, MAX_C), P = RandomTree(N), D = RandomD(N, 1, MAX_D));                       // Maximum N, Random
        CASE(N = MAX_N, C = rnd.nextLongLong(MAX_C / 10, MAX_C), P = RandomTree(N), D = RandomD(N, 1, 100));                // low number of chains.
        CASE(N = MAX_N, C = rnd.nextLongLong(1, 100), P = RandomTree(N), D = RandomD(N, 1, MAX_D));                         // high number of chains
        CASE(N = MAX_N, C = 6, P = RandomTree(N), D = RandomD(N, 1, MAX_D));                                                // high density CHT (~0.2N)
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(0, MAX_C), P = RandomTree(N), D = RandomD(N, 1, MAX_D));       // Random
        CASE(N = rnd.nextInt(1, MAX_N), C = rnd.nextLongLong(0, MAX_C), P = RandomTree(N), D = RandomD(N, 1, MAX_D));       // Random
    }

private:
    inline vector<int> RandomD(int N, int L, int R)
    {
        vector<int> ret;
        for (int i = 1; i < N; i++) ret.push_back(rnd.nextInt(L, R));
        return ret;
    }

    inline vector<int> LineTree(int N)
    {
        vector<int> ret;
        for (int i = 1; i < N; i++) ret.push_back(i - 1);
        return ret;
    }

    inline vector<int> StarTree(int N)
    {
        vector<int> ret;
        for (int i = 1; i < N; i++) ret.push_back(0);
        return ret;
    }

    inline vector<int> BinaryTree(int N)
    {
        vector<int> ret;
        for (int i = 1; i < N; i++) ret.push_back((i - 1) / 2);
        return ret;
    }

    inline vector<int> RandomTree(int N)
    {
        vector<int> ret;
        for (int i = 1; i < N; i++) ret.push_back(rnd.nextInt(0, i - 1));
        return ret;
    }

    inline vector<int> CatTree(int N, int C)
    {
        assert(1 <= C && C <= N);
        vector<int> ret = LineTree(C);
        for (int i = C; i < N; i++) ret.push_back(rnd.nextInt(0, C - 1));
        return ret;
    }

    inline vector<int> BroomTree(int N, int C)
    {
        assert(1 <= C && C <= N);
        vector<int> ret = LineTree(C);
        for (int i = C; i < N; i++) ret.push_back(C - 1);
        return ret;
    }

    inline vector<int> LDTree(int N, int K)
    {
        assert(K > 0);
        int p = -1, cnt = 0;
        vector<int> ret;
        for (int i = 1; i < N; i++)
        {
            if (cnt == 0) 
            {
                p++;
                cnt = rnd.nextInt(max(1, K - 2), K + 2);
            }
            ret.push_back(p);
            cnt--;
        }
        return ret;
    }

    inline void DFS(const vector<vector<pii>>& adj, int &cur, int u, int p)
    {
        int pv = cur;
        for (const auto &v : adj[u]) 
        {
            if (v.fst != p)
            {
                P[cur] = pv; D[cur] = v.snd; cur++;
                DFS(adj, cur, v.fst, u);
            }   
        }
    }
}; 
