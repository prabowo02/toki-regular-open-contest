#include <cstdio>
#include <vector>
using namespace std;
 
vector <int> parent;
vector <vector <int> > children;
vector <int> v, LCA, pathToRootCount;
vector <pair <int, int> > answers;
void showLCA(int x=0){
  if(children[x].empty()){
    pathToRootCount[x]=LCA[x];
  }else{
    pathToRootCount[x]=0;
    for(int i = 0;i < children[x].size();i ++){
      showLCA(children[x][i]);
      pathToRootCount[x]+=pathToRootCount[children[x][i]];
    }
  }
  LCA[x]=pathToRootCount[x]-LCA[x];
}
void getLCA(int x=0){
  for(int i = 0;i < children[x].size();i ++){
    LCA[x]-=LCA[children[x][i]];
    getLCA(children[x][i]);
  }
  if(x)
    LCA[parent[x]]-=LCA[x];
}
struct linkedList{
  struct node{
    int value;
    node *prev, *next;
    node(int value=0):value(value), prev(NULL), next(NULL){}
  };
  int size;
  node *begin, *end;
  linkedList():size(0), begin(NULL), end(NULL){}
  void push_back(int x){
    if(size==0){
      begin=end=new node(x);
    }else{
      end->next=new node(x);
      end->next->prev=end;
      end=end->next;
    }
    size++;
  }
  void push_back(linkedList x){
    if(x.size){
      if(size){
        end->next=x.begin;
        x.begin->prev=end;
        end=x.end;
      }else{
        size=x.size;
        begin=x.begin;
        end=x.end;
      }
    }
    size+=x.size;
  }
  void pop_back(){
    if(size==1){
      delete begin;
      delete end;
    }else{
      end=end->prev;
      delete end->next;
    }
    size--;
  }
  int back(){
    return end->value;
  }
  void pop_front(){
    if(size==1){
      delete begin;
      delete end;
    }else{
      begin=begin->next;
      delete begin->prev;
    }
    size--;
  }
  int front(){
    return begin->value;
  }
};
vector <linkedList> unpairedLeaves;
void pr(int x=0){
  if(children[x].empty()){
    for(int i = 0;i < v[x];i ++)
      unpairedLeaves[x].push_back(x);
  }else{
    for(int i = 0;i < children[x].size();i ++){
      pr(children[x][i]);
      unpairedLeaves[x].push_back(unpairedLeaves[children[x][i]]);
    }
    vector <int> f, b;
    for(int i = 0;i < LCA[x];i ++){
      f.push_back(unpairedLeaves[x].front());
      unpairedLeaves[x].pop_front();
      b.push_back(unpairedLeaves[x].back());
      unpairedLeaves[x].pop_back();
    }
    for(int i = 0;i < LCA[x];i ++){
      answers.push_back(make_pair(f[i], b[LCA[x]-1-i]));
    }
  }
}
vector <vector <int> > al;
void altc(int x=0){
  for(int i = 0;i < al[x].size();i ++){
    if(children[al[x][i]].empty()){
      parent[al[x][i]]=x;
      children[x].push_back(al[x][i]);
      altc(al[x][i]);
    }
  }
}
int main(){
  int n;
  scanf("%d", &n);
  parent.resize(n);
  children.resize(n);
  al.resize(n);
  for(int i = 1;i < n;i ++){
    int u, v;
    scanf("%d%d", &u, &v);u--;v--;
    al[u].push_back(v);
    al[v].push_back(u);
  }
  parent[0]=0;
  altc();
  al.clear();
  // for(int i = 1;i < n;i ++){
  //  scanf("%d", &parent[i]);parent[i]--;
  //  children[parent[i]].push_back(i);
  // }
  v.resize(n);
  for(int i = 0;i < n;i ++){
    scanf("%d", &v[i]);
  }
  LCA=v;
  pathToRootCount.resize(n, 0);
  showLCA();
  getLCA();
  unpairedLeaves.resize(n);
  pr();
  printf("%d\n", (int) answers.size());
  for(int i = 0;i < answers.size();i ++){
    printf("%d %d\n", answers[i].first+1, answers[i].second+1);
  }
}
