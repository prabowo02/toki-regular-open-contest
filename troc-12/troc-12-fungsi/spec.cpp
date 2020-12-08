#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

#define pii pair<int, int>
#define fst first
#define snd second
#define vpi vector<pii>
#define vi vector<int>
#define ll long long
#define pub push_back

using namespace std;
using namespace tcframe;

const int MAX1 = 100000, MAX2 = 1e9, ITR = 10000;
const bool DEBUGMODE = 0;
bool DBG = 0;
class ProblemSpec : public BaseProblemSpec
{
    protected:
      int A, B, KA, KB, LA, LB, Q;
      vector<int> QL, QR, ans;

      void InputFormat()
      {
          LINE(A, B, KA, KB, LA, LB);
          LINE(Q);
          LINES(QL, QR) % SIZE(Q);
      }

      void OutputFormat()
      {
          LINES(ans) % SIZE(Q);
      }

      void GradingConfig()
      {
          TimeLimit(1);
          MemoryLimit(64);
      }

      void Constraints()
      {
          CONS(1 <= (ll)A * B && (ll)A * B <= MAX1);
          CONS(1 <= Q && Q <= MAX1);
          CONS(0 <= KA && KA < A);
          CONS(0 <= KB && KB < B);
          CONS(1 <= LA && LA <= MAX2);
          CONS(1 <= LB && LB <= MAX2);
          CONS(eachElementBetween(QL, 1, MAX2));
          CONS(eachElementBetween(QR, 1, MAX2));
      }

      void Subtask1()
      {
          Points(100);
      }

    private:
      bool eachElementBetween(const vector<int> &A, int lo, int hi) 
      {
          for (int a: A) 
          {
             if (a < lo || a > hi) 
            {
              if (DEBUGMODE) cout<<"INVALID : "<<a<<"\n";
              return false;
            }
          }
          return true;
      }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
    protected:
      void SampleTestCase1()
      {
          Subtasks({1});
          Input({
            "4 6 2 2 9 2",
            "5",
            "6 7",
            "13 11",
            "4 10",
            "9 19",
            "9999 9999"
          });
          Output({
            "6",
            "11",
            "-1",
            "9",
            "9999"
          });
      }
      void BeforeTestCase()
      {
          adjOri.clear();
          whereInTheCycle.clear();
          nodeNumber.clear();

          partOfNode.clear();
          adjTree.clear();
          whichTree.clear();
          sparseTable.clear();
          nodeHeight.clear();

          memberOfTree.clear();
          cycleOfTree.clear();
          pluralCycles.clear();

          QL.clear(); QR.clear();
      }
      void AfterTestCase()
      {
          
      }

      void TestGroup1()
      {
          Subtasks({1});

          //Small Graphs
          CASE( 
            A = 4, B = 6, 
            manualQuery(10, 4),
            manualQuery(2, 9),
            manualQuery(12, 10),
            manualQuery(17, 20),
            MakeMYTC(A, B, KA = 3, KB = 1, LA = 3, LB = 11, 1000 - QL.size()));
          
          CASE(
            A = 2, B = 3,
            manualQuery(3, 4),
            manualQuery(2, 3),
            manualQuery(8, 3),
            manualQuery(4, 10),
            manualQuery(5, 5),
            MakeMYTC(A, B, KA = 0, KB = 0, LA = 5, LB = 1, 1000 - QL.size()));

          CASE(
            A = rnd.nextInt(1, 100), B = 1000 / A,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, 1000), LB = rnd.nextInt(1, 1000), 1000));

          CASE(
            A = 17, B = 53,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, 100), LB = rnd.nextInt(1, 2000), 1000));

          // Two trees, different parity.
          CASE(
            A = 2, B = 2,
            manualQuery(1, 100),
            manualQuery(2, 100),
            manualQuery(1, 99),
            manualQuery(213003, 31313313),
            MakeMYTC(A, B, KA = 0, KB = 1, LA = 2, LB = 2, MAX1 - QL.size()));

          // Two trees, different parity, cycle[Tree] > LCM(A, B)
          CASE(
            A = 2, B = 2,
            MakeMYTC(A, B, KA = 0, KB = 1, LA = rnd.nextInt(MAX2 / A) * A, LB = rnd.nextInt(MAX2 / B) * B, MAX1));

          // Line Tree (One Tree)
          CASE(
            A = 2, B = 1,
            manualQuery(1, 500),
            manualQuery(3, 500),
            manualQuery(4, 500),
            manualQuery(123, 369),
            MakeMYTC(A, B, KA = 0, KB = 0, LA = 2, LB = 1, MAX1 - QL.size()));
          CASE(
            A = MAX1, B = 1,
            MakeMYTC(A, B, KA = 0, KB = 0, LA = A, LB = 1, MAX1));

          // Line Tree (One Tree), cycle[Tree] > LCM(A, B)
          CASE(
            A = MAX1, B = 1,
            MakeMYTC(A, B, KA = 0, KB = 0, LA = rnd.nextInt(MAX2 / A - 1000, MAX2 / A) * A, LB = 1, MAX1));

          // Line Trees (Two)
          CASE(
            A = 315, B = 316,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = A, LB = B, MAX1));

          // Line Trees (Two), cycle[Tree] > LCM(A, B)
          CASE(
            A = rnd.nextInt(1, 1000), B = rnd.nextInt(1, MAX1 / A),
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, MAX2 / A) * A, LB = rnd.nextInt(1, MAX2 / B) * B, MAX1));

          // Single Node
          CASE(
            A = 1, B = 1,
            MakeMYTC(A, B, KA = 0, KB = 0, LA = 1, LB = 1, MAX1));
          CASE(
            A = 1, B = rnd.nextInt(1, MAX1),
            MakeMYTC(A, B, KA = 0, KB = rnd.nextInt(B), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));

          // Forest of Single Nodes
          CASE(
            A = 69420, B = 1,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = 0, LA = 69420, LB = 69420, MAX1));
          CASE(
            A = rnd.nextInt(MAX1 - 1000, MAX1), B = 1,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = 0, LA = rnd.nextInt(1, MAX2 / A) * A, LB = rnd.nextInt(1, MAX2 / A) * A, MAX1));

          // Multi Cycles
          CASE(
            A = 99856, B = 1,
            MakeMYTC(A, B, KA = 0, KB = 0, LA = rnd.nextInt(A), LB = 316, MAX1));

          CASE(
            A = 97969, B = 1,
            MakeMYTC(A, B, KA = 0, KB = 0, LA = rnd.nextInt(A), LB = rnd.nextInt(1, MAX2 / 313) * 313, MAX1));

          // Large Cycle (One Node)
          CASE(
            A = 4339, B = 23,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = 1, LB = 1, MAX1));

          // LCM(A, B) = B or A
          CASE(
            A = rnd.nextInt(1, 50), B = rnd.nextInt(1, MAX1 / A / A) * A,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, B - 1), LB = rnd.nextInt(1, B - 1), MAX1));

          CASE(
            A = rnd.nextInt(1, 20), B = rnd.nextInt(1, MAX1 / A / A) * A,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));

          CASE(
            B = rnd.nextInt(1, 50), A = rnd.nextInt(1, MAX1 / B / B) * B,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, A - 1), LB = rnd.nextInt(1, A - 1), MAX1));

          CASE(
            B = rnd.nextInt(1, 20), A = rnd.nextInt(1, MAX1 / B / B) * B,
            MakeMYTC(A, B, KA = rnd.nextInt(A), KB = rnd.nextInt(B), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));

          // Random (Large) Prime Cases
          CASE(A = 673, B = 139,
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, LCM(A, B) - 1), LB = rnd.nextInt(1, LCM(A, B) - 1), rnd.nextInt(1, MAX1)));

          CASE(A = 1009, B = 97,
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), rnd.nextInt(1, MAX1)));
          
          // Random Cases, LA, LB < LCM(A, B)
          CASE(
            A = rnd.nextInt(1, 100000), B = rnd.nextInt(1, MAX1 / A),
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, LCM(A, B) - 1), LB = rnd.nextInt(1, LCM(A, B) - 1), rnd.nextInt(1, MAX1)));
          CASE(
            A = rnd.nextInt(1, 5000) , B = rnd.nextInt(1, MAX1 / A),
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, LCM(A, B) - 1), LB = rnd.nextInt(1, LCM(A, B) - 1), rnd.nextInt(1, MAX1)));
          CASE(
            A = rnd.nextInt(1, 1000) , B = rnd.nextInt(1, MAX1 / A),
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, LCM(A, B) - 1), LB = rnd.nextInt(1, LCM(A, B) - 1), rnd.nextInt(1, MAX1)));
          
          // Random Cases
          CASE(
            A = rnd.nextInt(1, 1000) , B = rnd.nextInt(1, MAX1 / A), 
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));
          CASE(
            A = rnd.nextInt(1, 100000) , B = rnd.nextInt(1, MAX1 / A),
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));
          CASE(
            A = rnd.nextInt(1, 5000) , B = rnd.nextInt(1, MAX1 / A), 
            MakeMYTC(A, B, KA = rnd.nextInt(0, A - 1), KB = rnd.nextInt(0, B - 1), LA = rnd.nextInt(1, MAX2), LB = rnd.nextInt(1, MAX2), MAX1));
          

          /* OLD CASE TEMPLATE
          CASE(
            initialize(A = , B = , KA = , KB = , LA = , LB = ),
            MDCQuery(500, MAX2),
            MDFLQuery(8000, MAX2),
            MNPQuery(100, MAX2),
            MVQuery(10000, MAX2),
            MOLQuery(2000, MAX2),
            MSNQuery(500, MAX2),
            MRQuery(6000, MAX2),
            RandomizeQuery(),
            Q = (int)QL.size()
            );
          */
      }

    private:
      // Original Nodes
      vector<pii> adjOri;                           // Adjacency List for the original graph
      vector<ll> whereInTheCycle;                   // Distance towards origin cycle (true root)
      vector<int> nodeNumber;                       // Original's node number -> tree node

      // Tree Nodes
      vector<vi> partOfNode;                        // Keeps which nodes in the original graph are part of a node in the tree
      vector<vpi> adjTree;                          // Adjacency List for the tree
      vector<int> whichTree;                        // tree node -> which graph
      vector<vector<pair<int, ll>>> sparseTable;
      vector<int> nodeHeight;
      
      // Tree Graphs
      vector<ll> cycleOfTree;                       // Size of cycle at the root of tree
      vector<vi> memberOfTree;                      // Keeps members of the same tree, with the root at index 0
      vector<int> pluralCycles;

      int N;                                        // Size of graph.
      
      int GCD(int a, int b) {return b ? GCD(b, a % b) : a;}
      int LCM(int a, int b) {return a / GCD(a, b) * b;}
      ll MOD(ll a, ll m) {return (a % m + m) % m;}

      void newTNode()
      {
          adjTree.pub(vpi());
          whichTree.pub(0);
          partOfNode.pub(vi());
      }
      
      void newTree()
      {
          memberOfTree.pub(vi());
          cycleOfTree.pub(0);
      }

      void assignNode(int node, int id, ll val)
      {
          nodeNumber[node] = id;
          partOfNode[id].pub(node);
          whereInTheCycle[node] = val;
      }

      void assignTreeNode(int node, int tree_id)
      {
          whichTree[node] = tree_id;
          memberOfTree[tree_id].pub(node);
      }

      void updCycTree(int node, ll val)
      {
          cycleOfTree[node] = val;
      }

      int latestTNodeID() {return adjTree.size() - 1;}

      int latestTreeID() {return memberOfTree.size() - 1;}

      void newEdge(int node_a, int node_b, ll c) {adjTree[nodeNumber[node_a]].pub({nodeNumber[node_b], c});}

      int buildTree(int node)
      {
          int cyc = -1;
          nodeNumber[node] = -2;
          //cout << "DFS " << node <<"\n";
          if (nodeNumber[adjOri[node].fst] == -1) // Traverse when not traversed
          {
             cyc = buildTree(adjOri[node].fst);
          }        
          if (adjOri[node].fst == node) // If it is a self loop
          {
              newTNode();
              newTree();
              assignTreeNode(latestTNodeID(), latestTreeID());
              assignNode(node, latestTNodeID(), 0);
              updCycTree(latestTreeID(), adjOri[node].snd);
          }
          else if (cyc == -1) // Out of cycle / first node of cycle
          {
              newTNode();
              if (nodeNumber[adjOri[node].fst] != -2) // Extra commands for out of cycle.
              {
                  assignNode(node, latestTNodeID(), whereInTheCycle[adjOri[node].fst] + adjOri[node].snd);
                  assignTreeNode(latestTNodeID(), whichTree[nodeNumber[adjOri[node].fst]]);
                  newEdge(adjOri[node].fst, node, adjOri[node].snd);
              }
              else // Extra commands for 1st node of cycle
              {
                 newTree();
                 assignNode(node, latestTNodeID(), adjOri[node].snd);
                 assignTreeNode(latestTNodeID(), latestTreeID());
                 cyc = adjOri[node].fst;
              }
          }
          else // Nodes which are part of a cycle
          {
              assignNode(node, latestTNodeID(), whereInTheCycle[adjOri[node].fst] + adjOri[node].snd);
              if (cyc == node)
              {
                  updCycTree(latestTreeID(), whereInTheCycle[node]);
                  whereInTheCycle[node] = 0;
                  cyc = -1;
              }
          }
          return cyc;
      }

      void buildSparse(int u, int p, int c)
      {
          nodeHeight[u] = (p + 1) ? (nodeHeight[p] + 1) : 0;
          sparseTable[u][0] = {p, c};
          for (int i = 1; (1 << i) <= adjTree.size(); i++)
          {
              if (sparseTable[u][i - 1].fst + 1)
              {
                  sparseTable[u][i].fst = sparseTable[sparseTable[u][i - 1].fst][i - 1].fst;
                  sparseTable[u][i].snd = sparseTable[u][i - 1].snd + sparseTable[sparseTable[u][i - 1].fst][i - 1].snd;
              }
          }
          for (auto v : adjTree[u]) 
          {
            buildSparse(v.fst, u, v.snd);
          }
      }

      pii earliestPossibleNumToRoot(int node1, int node2, int LIM)
      {
          ll dst1 = 0, dst2 = 0, tp1 = nodeNumber[node1], tp2 = nodeNumber[node2];
          for (int i = 1, j = 0; i <= adjTree.size(); i <<= 1, j++)
          {
            if (nodeHeight[tp1] & i) {dst1 += sparseTable[tp1][j].snd; node1 = sparseTable[tp1][j].fst;}
            if (nodeHeight[tp2] & i) {dst2 += sparseTable[tp2][j].snd; node2 = sparseTable[tp2][j].fst;}
          }
          dst1 += MOD(whereInTheCycle[node2] - whereInTheCycle[node1], cycleOfTree[whichTree[nodeNumber[node1]]]);
          if (max((dst1 - node1 + N - 1) / N * N + node1, (dst2 - node2 + N - 1) / N * N + node2) > LIM) {return {-1, -1};}
          else {return {(dst1 - node1 + N - 1) / N * N + node1, (dst2 - node2 + N - 1) / N * N + node2};}
      }

      pii earliestPossibleNum(int node1, int node2, int LIM)
      {
          ll dst1 = 0, dst2 = 0, tp1 = nodeNumber[node1], tp2 = nodeNumber[node2]; int i;
          if (nodeHeight[tp1] > nodeHeight[tp2]) {swap(node1, node2); swap(tp1, tp2);}
          for (i = 0; (1 << i) <= adjTree.size(); i++)
          {
            if ((nodeHeight[tp2] - nodeHeight[tp1]) & (1 << i)) {dst2 += sparseTable[tp2][i].snd; tp2 = sparseTable[tp2][i].fst;}
          }
          if (DBG) cout << "DST : "<<dst1<<" "<<dst2<<" "<<nodeHeight[tp1]<<" "<<nodeHeight[tp2]<<" "<<i<<"\n";
          for (i--; i >= 0; i--)
          {
            if (sparseTable[tp1][i].fst != sparseTable[tp2][i].fst)
            {
              dst1 += sparseTable[tp1][i].snd;
              dst2 += sparseTable[tp2][i].snd;
              tp1 = sparseTable[tp1][i].fst;
              tp2 = sparseTable[tp2][i].fst;
            }
          }
          if (DBG) cout << "DST : "<<dst1<<" "<<dst2<<" "<<nodeHeight[tp1]<<"\n";
          if (tp1 != tp2)
          {
              dst1 += sparseTable[tp1][0].snd;
              dst2 += sparseTable[tp2][0].snd;
              tp1 = sparseTable[tp1][0].fst;
              tp2 = sparseTable[tp2][0].fst;
          }
          if (DBG) cout << "DST : "<<dst1<<" "<<dst2<<" "<<tp1<<" " <<tp2<<"\n";
          if (nodeHeight[tp1] == 0) 
          {
            dst1 = whereInTheCycle[node1];
            dst2 = whereInTheCycle[node2];
          }
          if (DBG) cout << "DST : "<<dst1<<" "<<dst2<<"\n";
          int lca = partOfNode[tp1].back();
          if (max(dst1, dst2) + lca > LIM) {return {-1, -1};}
          else {return {dst1 + lca, dst2 + lca};}
      }

      int getRandNode(int id) {return partOfNode[id][rnd.nextInt(partOfNode[id].size())];}

      int getRandTNode(int id) {return memberOfTree[id][rnd.nextInt(memberOfTree[id].size())];}

      int getRandNum(int id, ll cycSize, ll LIM)
      {
          ll mx = (LIM - id) / cycSize;
          if (id == 0 && mx == 0) {return N;}
          else if (id == 0) {return rnd.nextInt(1, mx) * cycSize + id;}
          return rnd.nextInt(0, mx) * cycSize + id;
      }

      int getRoot(int node)
      {
          return partOfNode[memberOfTree[whichTree[nodeNumber[node]]].front()].back();
      }

      int earliestPossibleQuery(int node)
      {
          return whereInTheCycle[node] + getRoot(node);
      } 

      void manualQuery(int a, int b) {QL.pub(a); QR.pub(b);}  // Manual queries

      bool disconnectedTreeQuery(int LIM)  // Queries where the nodes are disconnected (Invalid)
      {
          if (memberOfTree.size() == 1) {return 0;} // In case it is not a forest graph
          int tree1 = rnd.nextInt(memberOfTree.size()), tree2 = rnd.nextInt(memberOfTree.size() - 1);
          if (tree2 >= tree1) {tree2++;}
          int node1 = getRandNode(getRandTNode(tree1)), node2 = getRandNode(getRandTNode(tree2));
          QL.pub(getRandNum(node1, N, LIM));
          QR.pub(getRandNum(node2, N, LIM));
          return 1;
      }

      bool differentCycleOneTreeQuery(int LIM)  // Queries where the nodes are in different periods of the cycle on the same tree. (Invalid)
      {
          if (pluralCycles.size() == 0) {return 0;}
          int tree = pluralCycles[rnd.nextInt(pluralCycles.size())];
          int node1 = getRandNode(getRandTNode(tree)), node2 = getRandNode(getRandTNode(tree));
          pii tp = earliestPossibleNum(node1, node2, LIM);
          //cout << node1 << " " << node2 << " " << tp.fst << " "<< tp.snd << "ST\n";
          if (tp.fst == -1) {return 0;}
          if (min(tp.fst, tp.snd) + N > LIM) {return 0;}
          ll ft, sd;
          if (tp.fst > tp.snd)
          {
              ft = rnd.nextInt(min(cycleOfTree[tree] / N, (ll)(LIM - tp.fst) / N + 1));
              sd = rnd.nextInt(min(cycleOfTree[tree] / N, (ll)(LIM - tp.snd) / N + 1) - 1);
              if (ft <= sd) {sd = (sd + 1) % min((ll)(LIM - tp.fst) / N + 1, cycleOfTree[tree] / N);}
          }
          else
          {
              ft = rnd.nextInt(min(cycleOfTree[tree] / N, (ll)(LIM - tp.fst) / N + 1) - 1);
              sd = rnd.nextInt(min(cycleOfTree[tree] / N, (ll)(LIM - tp.snd) / N + 1));
              if (sd <= ft) {ft = (ft + 1) % min((ll)(LIM - tp.snd) / N + 1, cycleOfTree[tree] / N);}
          }
          QL.pub(getRandNum(ft * N + node1, cycleOfTree[tree], LIM));
          QR.pub(getRandNum(sd * N + node2, cycleOfTree[tree], LIM));
          //cout << node1 << " " << node2 << " " << tp.fst << " "<< tp.snd << "EN\n";
          return 1;
      }

      bool nonPositiveQuery(int LIM) // Queries where there technically exists an answer, however it is non-positive. (Invalid)
      {
          int tree = rnd.nextInt(memberOfTree.size());
          int node1 = getRandNode(getRandTNode(tree)), node2 = getRandNode(getRandTNode(tree));
          pii tp = earliestPossibleNum(node1, node2, LIM);
          if (tp.fst == -1) {return 0;}
          if (tp.fst > cycleOfTree[tree]) {tp.fst -= rnd.nextInt(0, tp.fst / cycleOfTree[tree]) * cycleOfTree[tree]; tp.snd = getRandNum(tp.snd, cycleOfTree[tree], LIM);}
          else if (tp.snd > cycleOfTree[tree]) {tp.snd -= rnd.nextInt(0, tp.snd / cycleOfTree[tree]) * cycleOfTree[tree]; tp.fst = getRandNum(tp.fst, cycleOfTree[tree], LIM);}
          else {return 0;}
          QL.pub(tp.fst);
          QR.pub(tp.snd);
          return 1;
      }

      bool validQuery(int LIM) // Literally that. (Valid)
      {
          int tree = rnd.nextInt(memberOfTree.size());
          int node1 = getRandNode(getRandTNode(tree)), node2 = getRandNode(getRandTNode(tree));
          pii tp = earliestPossibleNum(node1, node2, LIM);
          //cout << node1 << " "<< node2 << " " << tp.fst << " " << tp.snd << "\n";
          if (tp.fst == -1) {return 0;}
          QL.pub(getRandNum(tp.fst, cycleOfTree[tree], LIM));
          QR.pub(getRandNum(tp.snd, cycleOfTree[tree], LIM));
          return 1;
      }

      bool oneLoopQuery(int LIM) // The query exists within the root node (valid)
      {
          int tree = rnd.nextInt(memberOfTree.size());
          int node1 = getRandNode(memberOfTree[tree].front()), node2 = getRandNode(memberOfTree[tree].front());
          pii tp = earliestPossibleNum(node1, node2, LIM);
          if (tp.fst == -1) {return 0;}
          QL.pub(getRandNum(tp.fst, cycleOfTree[tree], LIM));
          QR.pub(getRandNum(tp.snd, cycleOfTree[tree], LIM));
          return 1;
      }

      void sameNodeQuery(int LIM) // The query exists within the exact same (original) node, however on (could be) different periods of the cycle (valid)
      {
          int node = rnd.nextInt(N);
          if (earliestPossibleQuery(node) < LIM)
          {
              QL.pub(getRandNum(node, cycleOfTree[whichTree[nodeNumber[node]]], LIM));
              QR.pub(getRandNum(node, cycleOfTree[whichTree[nodeNumber[node]]], LIM));
          }
          else 
          {
            if (node == 0) {node = N;}
            QL.pub(node); QR.pub(node);
          }
      }

      void totalRandomnessQuery(int LIM) // Literally that (undeterminable)
      {
         QL.pub(rnd.nextInt(1, LIM));
         QR.pub(rnd.nextInt(1, LIM));
      }

      bool isLatestValid()
      {
         if (QL.size() == 0) {return 1;}
         if (QL.back() < 1 || QL.back() > MAX2 || QR.back() < 1 || QR.back() > MAX2) {return 0;}
         else {return 1;}
      } 

      void MDCQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            int j;
            for (j = 0; j < ITR && !disconnectedTreeQuery(LIM); j++) {}
            if (j == ITR) {break;}
            if (DEBUGMODE) if (!isLatestValid()) {cout << QL.back() << " " << QR.back() << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"Disconnected Query done\n";
      }

      void MDFLQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            int j;
            for (j = 0; j < ITR && !differentCycleOneTreeQuery(LIM); j++) {}
            if (j == ITR) {break;}
            if (!isLatestValid() && DEBUGMODE) 
            {
              cout << QL.back() << " " << QR.back() << "LOLWRONG\n";
              cout << QL.back() % N << " " << QR.back() % N << "\n";
              DBG = 1;
              pii tp  = earliestPossibleNum(QL.back() % N, QR.back() % N, LIM);
              DBG = 0;
              cout << "EPQ : " << tp.fst << " " << tp.snd << "\n";
            }
          }
          if (DEBUGMODE) cout<<"Different Cycles Query done\n";
      }

      void MNPQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            int j;
            for (j = 0; j < ITR && !nonPositiveQuery(LIM); j++) {}
            if (j == ITR) {break;}
            if (DEBUGMODE) if (!isLatestValid()) {cout << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"Non Positive Query done\n";
      }

      void MVQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            int j;
            for (j = 0; j < ITR && !validQuery(LIM); j++) {}
            if (j == ITR) {break;}
            if (DEBUGMODE) if (!isLatestValid()) {cout << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"Valid Query done\n";
      }

      void MOLQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            int j;
            for (j = 0; j < ITR && !oneLoopQuery(LIM); j++) {}
            if (j == ITR) {break;}
            if (DEBUGMODE) if (!isLatestValid()) {cout << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"One Loop Query done\n";
      }

      void MSNQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            sameNodeQuery(LIM);
            if (DEBUGMODE) if (!isLatestValid()) {cout << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"Same Node Query done\n";
      }

      void MRQuery(int T, int LIM)
      {
          for (int i = 0; i < T; i++) 
          {
            totalRandomnessQuery(LIM);
            if (DEBUGMODE) if (!isLatestValid()) {cout << "LOLWRONG\n";}
          }
          if (DEBUGMODE) cout<<"Random Query done\n";
      }

      void initialize(int A, int B, int KA, int KB, int LA, int LB)
      {
          N = LCM(A, B);
          for (int i = 0; i < N; i++) 
          {
              if (i % A == KA) {adjOri.pub({MOD(i - LA, N), LA});}
              else if (i % B == KB) {adjOri.pub({MOD(i - LB, N), LB});}
              else {adjOri.pub({MOD(i - 1, N), 1});}
              whereInTheCycle.pub(0);
              nodeNumber.pub(-1);
          }
          if (DEBUGMODE) cout << "Original Adjacency List Built\n";
          for (int i = 0; i < N; i++)
          {
              if (nodeNumber[i] == -1) {buildTree(i);}
          }
          if (DEBUGMODE) cout << "Tree Built\n";
          if (DEBUGMODE) cout << "Trees : "<<memberOfTree.size()<<"\n";
          if (DEBUGMODE) cout << "Tree Nodes : "<<adjTree.size()<<"\n";
          if (DEBUGMODE) 
          for (int i = 0; i <memberOfTree.size(); i++)
          {
            cout << "Tree "<<i<<" : \n";
            cout << "Cycle Size - " << cycleOfTree[i]<<"\n";
            cout << "Root Number - " << memberOfTree[i].front() << "\n";
          }

          for (int i = 0; i < adjTree.size(); i++)
          {
              nodeHeight.pub(-1);
              sparseTable.pub(vector<pair<int, ll>>());
              for (int j = 1; j <= adjTree.size(); j <<= 1)
              {
                sparseTable.back().pub({-1, 0});
              }
          }
          if (DEBUGMODE) cout<<"Sparse table initialized\n";

          for (int i = 0; i < memberOfTree.size(); i++)
          {
              if (cycleOfTree[i] > N) {pluralCycles.pub(i);}
              
              buildSparse(memberOfTree[i].front(), -1, 0);
          }
          if (DEBUGMODE) cout<<"Sparse table built\n";

      }

      void RandomizeQuery()
      {
          vector<int> NQL, NQR, randomizeOrder(QL.size());
          iota(randomizeOrder.begin(), randomizeOrder.end(), 0);
          rnd.shuffle(randomizeOrder.begin(), randomizeOrder.end());
          for (auto x :randomizeOrder)
          {
             NQL.pub(QL[x]);
             NQR.pub(QR[x]);
          }
          QL = NQL;
          QR = NQR;
          if (DEBUGMODE) cout << "Queries Randomized\n";
      }

      void MakeMYTC(int A, int B, int KA, int KB, int LA, int LB, int QQ)
      {
          int DC = 5 * QQ / 100, DFL = 10 * QQ / 100, NP = 8 * QQ / 100, V = 55 * QQ / 100, OL = 9 * QQ / 100, SN = 5 * QQ / 100, R = QQ - DC - DFL - NP - V - OL - SN;
          if (DEBUGMODE) cout << "\n";
          if (DEBUGMODE) cout<< "A = " << A << "\n";
          if (DEBUGMODE) cout<< "B = " << B << "\n";
          if (DEBUGMODE) cout<< "KA = "<< KA << "\n";
          if (DEBUGMODE) cout<< "KB = "<< KB << "\n";
          if (DEBUGMODE) cout<< "LA = "<< LA << "\n";
          if (DEBUGMODE) cout<< "LB = "<< LB << "\n";
          if (DEBUGMODE) cout<< "QQ = "<< QQ << "\n";
          initialize(A, B, KA, KB, LA, LB);
          MDCQuery(DC, MAX2);
          MDFLQuery(DFL, MAX2);
          MNPQuery(NP, MAX2);
          MVQuery(V, MAX2);
          MOLQuery(OL, MAX2);
          MSNQuery(SN, MAX2);
          MRQuery(R, MAX2);
          RandomizeQuery();
          Q = (int)QL.size();
      }
};