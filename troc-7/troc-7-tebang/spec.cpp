#include <tcframe/spec.hpp>
using namespace tcframe;

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> U;
    vector<int> V;
    int ANS;
    void InputFormat() {
        LINE(N);
        LINES(U, V) % SIZE(N - 1);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(2 <= N && N <= MAXN);
        CONS(inRange(U, 1, N));
        CONS(inRange(V, 1, N));
        CONS(isTree(U, V));
    }

    void Subtask1(){

    }

private:
    bool inRange(const vector<int> &v, int l, int r){
        for(int i : v)
            if(i < l || i > r)
                return false;
        return true;
    }

    bool isTree(const vector<int> &v, const vector<int> &u){
        if(u.size() != N - 1 || v.size() != N - 1)
            return false;
        vector<vector<int>> g(N);
        for(int i = 0; i < N - 1; i++){
            g[u[i] - 1].push_back(v[i] - 1);
            g[v[i] - 1].push_back(u[i] - 1);
        }
        queue<int> q;
        vector<bool> visit(N, false);
        q.push(0);
        visit[0] = true;
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int i : g[now]){
                if(!visit[i]){
                    q.push(i);
                    visit[i] = true;
                }
            }
        }
        for(int i = 0; i < N; i++)
            if(!visit[i])
                return false;
        return true;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "6",
            "1 2",
            "1 3",
            "1 4",
            "2 5",
            "2 6"

        });
        Output({
            "2"
        });
    }

    void TestGroup1() {
        Subtasks({1});


        CASE(N = 2, U = {1}, V = {2});
        CASE(N = 3, U = {1, 2}, V = {2, 3});
        for(int i = 0; i < 12; i++)
            CASE(N = MAXN, tie(U, V) = randomTree(N));
        for(int i = 0; i < 8; i++)
            CASE(N = rnd.nextInt(50000, MAXN), tie(U, V) = lineTree(N));
        for(int i = 0; i < 5; i++)
            CASE(N = rnd.nextInt(50000, MAXN), tie(U, V) = starTree(N));
    }   

    tuple<vector<int>, vector<int>> randomTree(int n){
        vector<int> node(n), u(n - 1), v(n - 1);
        for(int i = 0; i < n - 1; i++){
            u[i] = i + 1;
            v[i] = rnd.nextInt(0, i);
            if(rnd.nextInt(0, 1) == 1)
                swap(u[i], v[i]);
        }
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < n - 1; i++){
            u[i] = node[u[i]];
            v[i] = node[v[i]];
        }
        return make_tuple(u, v);
    }

    tuple<vector<int>, vector<int>> lineTree(int n){
        vector<int> node(n), u(n - 1), v(n - 1);
        for(int i = 0; i < n - 1; i++){
            u[i] = i + 1;
            v[i] = i;
            if(rnd.nextInt(0, 1) == 1)
                swap(u[i], v[i]);
        }
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < n - 1; i++){
            u[i] = node[u[i]];
            v[i] = node[v[i]];
        }
        return make_tuple(u, v);
    }

    tuple<vector<int>, vector<int>> starTree(int n){
        vector<int> node(n), u(n - 1), v(n - 1);
        int center = rnd.nextInt(0, n - 1);
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(i == center)
                continue;
            idx += 1;
            u[idx] = i;
            v[idx] = center;
            if(rnd.nextInt(0, 1) == 1)
                swap(u[idx], v[idx]);
        }
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < n - 1; i++){
            u[i] = node[u[i]];
            v[i] = node[v[i]];
        }
        return make_tuple(u, v);
    }

};
