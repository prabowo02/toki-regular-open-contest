#include <tcframe/spec.hpp>
#include <iostream>
#include <assert.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define vi vector<int>
#define ll long long
using namespace tcframe;
const ll MAX_N = 500, MAX_A = 1000000000;

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

class ProblemSpec : public BaseProblemSpec 
{
protected:
    int N, ans;
   	vector<vi> A;

    void InputFormat() 
    {
        LINE(N);
        GRID(A) % SIZE(N, N);
    }

    void OutputFormat() 
    {
        LINE(ans);
    }

    void GradingConfig() 
    {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() 
    {
        CONS(3 <= N && N <= MAX_N);
        CONS(checkGrid(A));
    }

    void Subtask1() 
    {
        Points(100);
    }

private:
    bool checkGrid(const vector<vi>& V)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (A[i][j] < 0 || A[i][j] > MAX_A) {return 0;}
                if (i == j) 
                {
                    if (A[i][j]) {return 0;}
                }
                else
                {
                    if (A[i][j] < 1 || A[i][j] != A[j][i]) {return 0;}
                }
            }
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
            "3",
            "0 1 2",
            "1 0 3",
            "2 3 0"
        });
        Output({
            "3"
        });
    }

    void SampleTestCase2() 
    {
        Subtasks({1});
        Input({
            "4",
            "0 2 6 2",
            "2 0 6 8",
            "6 6 0 5",
            "2 8 5 0"
        });
        Output({
            "6"
        });
    }

    void BeforeTestCase() 
    {
        A.clear(); 

        mapping.clear(); costs.clear();
        parent.clear(); members.clear(); color.clear();
        valid.clear(); invalid.clear();
    }

    void TestGroup1()
    {
        Subtasks({1});

        // Manual cases
        CASE(N = 9, EMapping(N), RUCosts(N), buildGraph(N), manualCase(N, {
                                                                            {0, 0, 0, 0, 0, 0, 0, 1, 0},
                                                                            {0, 0, 0, 0, 0, 9, 4, 0, 0},
                                                                            {0, 0, 0, 0, 0, 0, 0, 3, 8},
                                                                            {0, 0, 0, 0, 0, 2, 6, 0, 0},
                                                                            {0, 0, 0, 0, 0, 0, 0, 7, 5},
                                                                            {0, 9, 0, 2, 0, 0, 10, 0, 0},
                                                                            {0, 4, 0, 6, 0, 10, 0, 0, 0},
                                                                            {1, 0, 3, 0, 7, 0, 0, 0, 0},
                                                                            {0, 0, 8, 0, 5, 0, 0, 0, 0}
                                                                            })); // Disconnected case, could have been smaller, but ngeh.

        // Max N cases
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), maxBipartite(N, N / 2));                                //Largest Bipartite
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), maxBipartite(N, 1));                                    //Star
        CASE(N = MAX_N, RMapping(N), ECosts(N) , buildGraph(N), maxBipartite(N, 1));                                    //Equal costs
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), maxBipartite(N, rnd.nextInt(1, N)));                    //Random sized max bipartite
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, N * (N - 1) / 8 - 1));                   
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, 0)); 
        CASE(N = MAX_N, RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, rnd.nextInt(N * (N - 1) / 4)));
        CASE(N = MAX_N, RMapping(N), RCosts(N), buildGraph(N), randomEdges(N));

        // Random cases
        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RUCosts(N), buildGraph(N), maxBipartite(N, rnd.nextInt(1, N))); //Max

        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, rnd.nextInt(N * (N - 1) / 4))); // Random
        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, rnd.nextInt(N * (N - 1) / 4))); // Random
        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RUCosts(N), buildGraph(N), randomBipartite(N, rnd.nextInt(N * (N - 1) / 4))); // Random

        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RCosts(N), buildGraph(N), randomEdges(N)); //True Random
        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RCosts(N), buildGraph(N), randomEdges(N)); //True Random
        CASE(N = rnd.nextInt(3, MAX_N), RMapping(N), RCosts(N), buildGraph(N), randomEdges(N)); //True Random
    }

    void EMapping(int N) // Exact mapping
    {
        // cerr << "Enter exact mapping\n";
        for (int i = 0; i < N; i++) {mapping.push_back(i);}
        // cerr << "Exit exact mapping\n";
    }

    void RMapping(int N) // Random mapping
    {
        // cerr << "Enter random mapping\n";
        for (int i = 0; i < N; i++) {mapping.push_back(i);}
        rnd.shuffle(mapping.begin(), mapping.end());
        // cerr << "Exit random mapping\n";
    }

    void RCosts(int N) // Random costs
    {
        // cerr << "Enter R Cost mapping\n";
        for (int i = 0; i < N * (N - 1) / 2; i++) {costs.push_back(rnd.nextInt(1, MAX_A));}
        sort(costs.begin(), costs.end());
        // cerr << "Exit exact mapping\n";
    }

    void RUCosts(int N) // Random but unqiue costs
    {
        // cerr << "Enter RU Cost Mapping\n";
        set<int> C;
        for (int i = 0; i < N * (N - 1) / 2; i++)
        {
            int K = rnd.nextInt(1, MAX_A);
            while (C.count(K)) {K = rnd.nextInt(1, MAX_A);}
            C.insert(K); costs.push_back(K);
        }
        sort(costs.begin(), costs.end());
        // cerr << "Exit RU Cost Mapping\n";
    }

    void ECosts(int N) // Equal costs
    {
        // cerr << "Enter E Cost Mapping\n";
        int V = rnd.nextInt(1, MAX_A);
        for (int i = 0; i < N * (N - 1) / 2; i++) {costs.push_back(V);}
        // cerr << "Exit E Cost Mapping\n";
    }

    void buildGraph(int N)
    {
        // cerr << "Enter Graph Building\n";
        for (int i = 0; i < N; i++) {A.push_back(vi(N));}
        for (int i = 0; i < N; i++)
        {
            parent.push_back(i);
            color.push_back(0);
            members.push_back(vi());
            members.back().push_back(i);
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                valid.insert({i, j});
            }
        }
        // cerr << "Valid: " << valid.size() << "\n";
        // cerr << "Exit Graph Building\n";
    }

    void maxBipartite(int N, int L) //Maximum Bipartite Case
    {
        // cerr << "Enter maxbip\n";
        assert(L <= N);
        int p = 0;
        for (int i = 0; i < L; i++)
        {
            for (int j = L; j < N; j++)
            {
                setEdge(mapping[i], mapping[j], costs[p++]);
            }
        }
        vector<pair<int, int>> pk;
        for (int i = 0; i < L; i++)
        {
            for (int j = i + 1; j < L; j++) {pk.push_back(make_pair(mapping[i], mapping[j]));}
        }
        for (int i = L; i < N; i++)
        {
            for (int j = i + 1; j < N; j++) {pk.push_back(make_pair(mapping[i], mapping[j]));}
        }
        int k = rnd.nextInt(pk.size());
        setEdge(pk[k].first, pk[k].second, costs[p++]);
        for (int i = 0; i < pk.size(); i++)
        {
            if (i == k) continue;
            setEdge(pk[i].first, pk[i].second, costs[p++]);
        }
        // cerr << "Exit maxbip\n";
    }

    void randomBipartite(int N, int K) //The K-th (0 based) edge will be the first edge that is invalid (if possible)
    {
        // cerr << "Enter randbip\n";
        int p = 0;
        while ((p < K || invalid.size() == 0) && valid.size())
        {
            pair<int, int> ppp = *valid.find_by_order(rnd.nextInt(valid.size()));
            valid.erase(ppp);
            setEdge(ppp.first, ppp.second, costs[p++]);
            joinGroup(ppp.first, ppp.second); 
        }

        // cerr << "Invalid size : " << invalid.size() << ", Valid size : " << valid.size() << " " << "P: " << p << "\n";

        assert(invalid.size());
        pair<int, int> ppp = *invalid.find_by_order(rnd.nextInt(invalid.size()));
        invalid.erase(ppp);
        setEdge(ppp.first, ppp.second, costs[p++]);

        vector<pair<int, int>> leftover;
        for (const auto &x : valid) {leftover.push_back(x);}
        for (const auto &x : invalid) {leftover.push_back(x);}
        rnd.shuffle(leftover.begin(), leftover.end());

        for (const auto &X : leftover)
        {
            setEdge(X.first, X.second, costs[p++]);
        }
        // cerr << "Exit randbip\n";
    }

    void randomEdges(int N)
    {
        // cerr << "Enter randomedges\n";
        vector<pair<int, int>> order;
        for (int i = 0; i < N; i++) 
        {
            for (int j = i + 1; j < N; j++) order.push_back({i, j});
        }
        rnd.shuffle(order.begin(), order.end());
        for (int i = 0; i < N * (N - 1) / 2; i++)
        {
            setEdge(order[i].first, order[i].second, costs[i]);
        }
        // cerr << "Exit randomedges\n";
    }

    void manualCase(int N, vector<vi> V) // V[i][j] == 0 is unimportant.
    {
        assert(V.size() == N);
        int MX = 0;

        // cerr << "Entered Manual Case\n";

        for (int i = 0; i < N; i++) 
        {
            assert(V[i].size() == N);
            for (int j = 0; j < N; j++) {MX = max(MX, V[i][j]);}
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (V[i][j]) setEdge(mapping[i], mapping[j], costs[V[i][j] - 1]);
                else setEdge(mapping[i], mapping[j], costs[rnd.nextInt(MX, N * (N - 1) / 2 - 1)]);
            }
        }
        // cerr << "Exit Manual Case\n";
    }

private:
    vector<int> mapping, costs;
    vector<int> parent, color;
    vector<vi> members;
    ordered_set valid, invalid;

    void setEdge(int u, int v, int w)
    {
        assert(u != v && A[u][v] == 0 && A[v][u] == 0);
        A[u][v] = w;
        A[v][u] = w;
    }

    int findGroup(int u)
    {
        return parent[u] = (parent[u] == u) ? u : findGroup(parent[u]);
    }

    void joinGroup(int u, int v)
    {
        bool c = (color[u] == color[v]);
        u = findGroup(u), v = findGroup(v);
        if (u != v)
        {
            if (members[v].size() > members[u].size()) {swap(u, v);}
            parent[v] = u;
            for (const auto &y : members[v]) {color[y] ^= c;}
            for (const auto &x : members[u])
            {
                for (const auto &y : members[v])
                {
                    if (color[x] == color[y]) 
                    {
                        valid.erase({min(x, y), max(x, y)});
                        invalid.insert({min(x, y), max(x, y)});
                    }
                }
            }
            for (const auto &y : members[v]) {members[u].push_back(y);}
            members[v].clear();
        }
    }
}; 
