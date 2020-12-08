#include <bits/stdc++.h>
#define edge pair<int,trie*>
#define id first
#define node second
using namespace std;

const int MAXN=4e4+5;

int N, Q;
int A[MAXN];
int B[MAXN];
int K[MAXN];
int last[MAXN];
int ans[MAXN];
int pos[MAXN];

struct trie {
	int head;
	trie *par, *rot;
	vector <edge> child;
}
data, *now, *occ;
edge save;
queue <trie*> bfs;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	
	for (int i=0;i<N;i++) {
		cin>>A[i];
	}
	
	for (int i=N-1;i;i--) {
		A[i]^=A[i-1];
	}
	
	for (int i=1;i<=Q;i++) {
		cin>>K[i];
		
		for (int j=0;j<K[i];j++) {
			cin>>B[j];
		}
		
		for (int j=K[i]-1;j;j--) {
			B[j]^=B[j-1];
		}
		
		now=&data;
		
		for (int j=1;j<K[i];j++) {
			save={-1,NULL};
			
			for (edge next : now->child) {
				if (next.id==B[j]) {
					save=next;
					break;
				}
			}
			
			if (save.id==-1) {
				save.id=B[j];
				save.node=new trie;
				save.node->head=0;
				save.node->child.clear();
				now->child.push_back(save);
			}
			
			now=save.node;
		}
		
		if (!now->head) {
			now->head=i;
		}
		
		pos[i]=now->head;
	}
	
	bfs.push(&data);
	
	while (!bfs.empty()) {
		occ=bfs.front();
		bfs.pop();
		
		for (edge adj : occ->child) {
			save={-1,&data};
			now=occ->par;
			
			while (now) {
				for (edge next : now->child) {
					if (next.id==adj.id) {
						save=next;
						break;
					}
				}
				
				if (save.id==adj.id) {
					break;
				}
				
				now=now->par;
			}
			
			if (save.node->head) {
				adj.node->rot=save.node;
			}
			else {
				adj.node->rot=save.node->rot;
			}
			
			adj.node->par=save.node;
			bfs.push(adj.node);
		}
	}
	
	now=&data;
	
	for (int i=1;i<N;i++) {
		save={-1,&data};
		
		while (now) {
			for (edge next : now->child) {
				if (next.id==A[i]) {
					save=next;
					break;
				}
			}
			
			if (save.id==A[i]) {
				break;
			}
			
			now=now->par;
		}
		
		now=save.node;
		occ=now;
		
		if (!occ->head) {
			occ=occ->rot;
		}
		
		while (occ) {
			if (i-K[occ->head]+1>=last[occ->head]) {
				ans[occ->head]++;
				last[occ->head]=i+1;
			}
			
			if (i-K[occ->head]+1>=last[0]) {
				ans[0]++;
				last[0]=i+1;
			}
			
			occ=occ->rot;
		}
	}
	
	for (int i=1;i<=Q+1;i++) {
		cout<<ans[pos[i]]<<'\n';
	}
	
	return 0;
}
