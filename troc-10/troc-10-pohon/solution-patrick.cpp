#include <cstdio>
#include <vector>
using namespace std;

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
				size+=x.size;
			}else{
				size=x.size;
				begin=x.begin;
				end=x.end;
			}
		}
	}
	//push_front can be implemented but isn't necessary
	void pop_back(){
		if(size==1){
			delete begin;
			end=NULL;
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
			end=NULL;
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
vector <vector <int> > adjLis, child;
void dfs1(int x=0){//get children from adjacency list
	while(!adjLis[x].empty()){
		if(child[adjLis[x].back()].empty()){
			child[x].push_back(adjLis[x].back());
			dfs1(adjLis[x].back());
		}
		adjLis[x].pop_back();
	}
}
vector <int> w;
vector <int> upToRoot;//increment ancestors of queried integers
vector <int> diff;//upToRoot-w
void dfs2(int x=0){//get upToRoot and diff from w
	if(child[x].size()){
		upToRoot[x]=0;
		for(int i = 0;i < child[x].size();i ++){
			dfs2(child[x][i]);
			upToRoot[x]+=upToRoot[child[x][i]];
		}
	}else{
		upToRoot[x]=w[x];
	}
	diff[x]=upToRoot[x]-w[x];
}
vector <int> subtreesum;//of lca
vector <int> lca;//count of lca of queries
void dfs3(int x=0){//get lca and subtreesum from diff
	if(child[x].empty()){
		lca[x]=0;
		subtreesum[x]=0;
	}else{
		subtreesum[x]=0;
		for(int i = 0;i < child[x].size();i ++){
			dfs3(child[x][i]);
			subtreesum[x]+=subtreesum[child[x][i]];
		}
		lca[x]=diff[x]-2*subtreesum[x];
		subtreesum[x]+=lca[x];
	}
}
vector <linkedList> unpaired;//leaves
vector <pair <int, int> > answers;
void dfs4(int x=0){//get answers from lca and w
	if(child[x].empty()){
		for(int i = w[x];i --;){
			unpaired[x].push_back(x);
		}
	}else{
		for(int i = 0;i < child[x].size();i ++){
			dfs4(child[x][i]);
			unpaired[x].push_back(unpaired[child[x][i]]);
		}
		vector <int> reversePair;
		for(int i = lca[x];i --;){
			reversePair.push_back(unpaired[x].back());
			unpaired[x].pop_back();
		}
		for(int i = lca[x];i --;){
			answers.push_back(make_pair(reversePair.back(), unpaired[x].front()));
			reversePair.pop_back();
			unpaired[x].pop_front();
		}
	}
}
int main(){
	int n;
	scanf("%d", &n);
	adjLis.resize(n);
	for(int i = 1;i < n;i ++){
		int u, v;
		scanf("%d%d", &u, &v);u--;v--;
		adjLis[u].push_back(v);
		adjLis[v].push_back(u);
	}
	child.resize(n);
	dfs1();
	w.resize(n);
	for(int i = 0;i < n;i ++)
		scanf("%d", &w[i]);
	upToRoot.resize(n);
	diff.resize(n);
	dfs2();
	subtreesum.resize(n);
	lca.resize(n);
	dfs3();
	unpaired.resize(n, linkedList());
	dfs4();
	printf("%lu\n", answers.size());
	for(int i = 0;i < answers.size();i ++){
		printf("%d %d\n", answers[i].first+1, answers[i].second+1);
	}
}
