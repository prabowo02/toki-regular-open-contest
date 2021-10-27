#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

void ac()
{
	printf("AC\n");
	exit(0);
}

void wa()
{
	printf("WA\n");
	exit(0);
}

const int mxa=1e9; // Max coordinate.
int n;
long long bound; // Total path distance upperbound.
int seq[90069]; // Path sequence p.
pair<int,int> a[90069]; // Points.
bitset<90069> visit; // Visited array for permutation checking.
double total=0; // Current total path distance.

// AVL tree where only its leaves store values.
// A leaf maybe active or inactive.
// Active leaves store values, inactive leaves don't.
// All operations in the AVL don't change the addresses of existing leaves.
struct avltree
{
	int leaf=1; // Number of active leaves in its subtree.
	int height=1; // Height of its subtree.
	pair<int,int> maxHeight; // Maximum height out of its children's subtrees.
	int big=-1; // The child with the maximum height, -1 if it has no child.
	int ans; // Value stored (only used in leaves).
	avltree *child[2]; // Children, 0 is left, 1 is right.
	avltree *parent;
	
	// Assign values from children's values.
	void assign()
	{
		leaf=child[0]->leaf+child[1]->leaf;
		maxHeight=max(mp(child[0]->height,0),{child[1]->height,1});
		height=maxHeight.fr+1;
		big=maxHeight.sc;
	}
	
	// Subtree rotation, right rotate if direction=0, left rotate if direction=1.
	void rotate(int direction)
	{
		avltree *tmp=child[!direction];
		
		// Make a new node in the direction of the rotation.
		child[!direction]=new avltree;
		child[!direction]->parent=this;
		
		// Assign children to the new node.
		child[!direction]->child[direction]=child[direction]->child[!direction];
		child[!direction]->child[direction]->parent=child[!direction];
		child[!direction]->child[!direction]=tmp;
		tmp->parent=child[!direction];
		
		child[!direction]->assign();
		
		// Finish the opposite direction.
		child[direction]=child[direction]->child[direction];
		child[direction]->parent=this;
		
		assign();
	}
	
	// Check if it's unbalanced.
	void check()
	{
		assign();
		
		if(abs(child[0]->height-child[1]->height)>1)
		{
			// Rotate big child if big's big child isn't in the same direction.
			if(child[big]->big!=big)
			{
				child[big]->rotate(!big);
			}
			
			rotate(big);
		}
	}
	
	// Initialize the AVL tree by making it a complete binary tree with two leaves that are inactive.
	// This eliminates any corner case in insertion.
	void init()
	{
		int ii;
		
		for(ii=0;ii<2;ii++)
		{
			child[ii]=new avltree;
			child[ii]->leaf=0;
			child[ii]->parent=this;
		}
		
		assign();
	}
	
	// Insert a leaf with value w in between order x and x+1.
	// Returns the address of the new leaf.
	avltree* insert(int x,int w)
	{
		int ii;
		avltree *tmp;
		
		// Get which target child to recurse into and change x accordingly.
		for(ii=0;ii<2;ii++)
		{
			if(x<=child[ii]->leaf)
			{
				break;
			}
			x-=child[ii]->leaf;
		}
		
		// Insert new leaf if the target child is a leaf.
		if(child[ii]->height==1)
		{
			tmp=child[ii];
			
			// Make a new node in place of the target child.
			child[ii]=new avltree;
			child[ii]->parent=this;
			
			// Assign the existing leaf as one child.
			child[ii]->child[!x]=tmp;
			tmp->parent=child[ii];
			
			// Assign a new leaf as the other child.
			child[ii]->child[x]=new avltree;
			child[ii]->child[x]->ans=w;
			child[ii]->child[x]->parent=child[ii];
			
			child[ii]->assign();
			
			tmp=child[ii]->child[x];
		}
		else
		{
			tmp=child[ii]->insert(x,w);
		}
		
		check();
		
		return tmp;
	}
	
	// Erase the leaf at order x by making it inactive.
	void erase(int x)
	{
		if(height==1)
		{
			leaf=0;
		}
		else
		{
			int ii;
			
			// Get which target child to recurse into and change x accordingly.
			for(ii=0;ii<2;ii++)
			{
				if(x<=child[ii]->leaf)
				{
					break;
				}
				x-=child[ii]->leaf;
			}
			
			child[ii]->erase(x);
			
			assign();
		}
	}
	
	// Query the value of the leaf at order x.
	int query(int x)
	{
		if(height==1)
		{
			return ans;
		}
		else
		{
			int ii;
			
			// Get which target child to recurse into and change x accordingly.
			for(ii=0;ii<2;ii++)
			{
				if(x<=child[ii]->leaf)
				{
					break;
				}
				x-=child[ii]->leaf;
			}
			
			return child[ii]->query(x);
		}
	}
};
avltree root;
avltree *position[90069]; // The address of each element in p.

// Euclidean distance between two points.
double distance(pair<int,int> p,pair<int,int> p2)
{
	int distanceX=p.fr-p2.fr,distanceY=p.sc-p2.sc;
	
	return sqrt((long long)distanceX*distanceX+(long long)distanceY*distanceY);
}

// Check if the total distance is out of bounds.
void check()
{
	if(total>=bound)
	{
		wa();
	}
}

int main(int argc,char *argv[])
{
	ifstream inp(argv[1]);
	ifstream out(argv[2]);
	ifstream con(argv[3]);
	
	int q,i,k,before,after,order,x,y,p;
	avltree *tmp;
	
	inp>>n;
	
	bound=(long long)n*2*mxa;
	
	for(i=1;i<=n*n;i++)
	{
		inp>>a[i].fr>>a[i].sc;
	}
	
	//Initialize AVL.
	root.init();
	
	for(i=1;i<=n*n;i++)
	{
		if(!(con>>seq[i]))
		{
			wa();
		}
		
		// Permutation check.
		if(seq[i]<0||seq[i]>n*n||visit[seq[i]])
		{
			wa();
		}
		visit[seq[i]]=1;
		
		if(i>1)
		{
			total+=distance(a[seq[i-1]],a[seq[i]]);
		}
		
		// Insert into AVL and get its address.
		position[seq[i]]=root.insert(i-1,seq[i]);
	}
	
	check();
	
	inp>>q;
	for(i=0;i<q;i++)
	{
		inp>>k>>x>>y;
		if(!(con>>p))
		{
			wa();
		}
		
		if(p<0||p>n*n)
		{
			wa();
		}
		
		// Get the order of element k in AVL.
		order=1;
		for(tmp=position[k];tmp!=&root;tmp=tmp->parent)
		{
			// If tmp is a right child, add the number of active leaves of the left child.
			if(tmp==tmp->parent->child[1])
			{
				order+=tmp->parent->child[0]->leaf;
			}
		}
		
		// Erase k and update the total distance.
		if(order>1)
		{
			before=root.query(order-1);
			total-=distance(a[before],a[k]);
		}
		if(order<n*n)
		{
			after=root.query(order+1);
			total-=distance(a[k],a[after]);
		}
		if(order>1&&order<n*n)
		{
			total+=distance(a[before],a[after]);
		}
		root.erase(order);
		
		a[k]={x,y};
		
		// Insert k, get its new address, and update the total distance.
		position[k]=root.insert(p-1,k);
		if(p>1)
		{
			before=root.query(p-1);
			total+=distance(a[before],a[k]);
		}
		if(p<n*n)
		{
			after=root.query(p+1);
			total+=distance(a[k],a[after]);
		}
		if(p>1&&p<n*n)
		{
			total-=distance(a[before],a[after]);
		}
		check();
	}
	
	if(con>>k)
	{
		wa();
	}
	
	ac();
}
