/*
 *    J1K7_7
 *
 *    You can use my contents on a Creative Commons - Attribution 4.0 International - CC BY 4.0 License.  XD 
 *    - JASKAMAL KAINTH
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <cassert>
#include <list>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <limits>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define left(x) 		   (x << 1)
#define right(x) 		   (x << 1) + 1
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define ff                  first
#define ss                 second
const int maxn = 3e5+7;
int n; // number of nodes

vector<int> G[maxn];
int low[maxn], disc[maxn] , parent[maxn] , vis[maxn];
vector<pair<int,int> > bedge; // all bridge edges 
int timer;
vector<int> Btree[maxn]; 

int rankN[maxn];
int parentN[maxn];
inline void make_set()
{
	for(int i = 0; i < n; i++)
		parentN[i] = rankN[i] = i;  
}
inline int find_set(int u)
{
	if(parentN[u] != u )
		parentN[u] = find_set(parentN[u]);
	return parentN[u];
}
inline void union_set(int u,int v)
{
	int pu = find_set(u);
	int pv = find_set(v);
	if(pu == pv)
		return ;
	if(rankN[pu] > rankN[pv])
	{
		parentN[pv] = pu;  
	}
	else
	{
		parentN[pu] = pv;
		if(rankN[pu] == rankN[pv])
			rankN[pv]++;
	}
}
inline void init_bridge_tree()
{
	make_set();
	timer = 0;
	for(int i = 0; i < maxn; i++)
	{
		low[i] = disc[i] = vis[i] = 0;
		parent[i] = -1;
	}
}
/* Mark all the bridges */
inline void mark_bridges(int u)
{
	vis[u] = 1;
	disc[u] = low[u] = timer++;
	for(int &v: G[u])
	{
		if(!vis[v])
		{
			parent[v] = u;
			mark_bridges(v);
			low[u] = min(low[u],low[v]);
			if(low[v] > disc[u])
			{
				bedge.push_back(mp(u,v));
			}
			else
			{
				union_set(u,v);
			}
		}
		else if(parent[u] != v)
		{
			low[u] = min(low[u],disc[v]);
		}
	}
}
inline void make_tree()
{
	init_bridge_tree();
	mark_bridges(0); // mark all the bridges
	for(auto &i: bedge) // atmose n-1 bridge edges.
	{
		int pu = find_set(i.ff);
		int pv = find_set(i.ss);
		if(pu != pv)
		{
			Btree[pu].push_back(pv);
			Btree[pv].push_back(pu);
		}
	}
}
const int MAXN = 3e5+7; 
const int MAXLOG = 20; 

int P[MAXN][MAXLOG]; // initially all -1
int d[MAXN];
void dfs1(int v,int p = -1){
	P[v][0] = p;
	if(p + 1)
		d[v] = d[p] + 1;
	for(int i = 1;i < MAXLOG;i ++)
		if(P[v][i-1] + 1)
			P[v][i] = P[P[v][i-1]][i-1];
	for(auto u : Btree[v])
		if(p - u)
			dfs1(u,v);
}
void process3(int N  = n)
{
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; 1 << j < N; j++)
			P[i][j] = -1;
	for (j = 1; 1 << j < N; j++)
		for (i = 0; i < N; i++)
			if (P[i][j - 1] != -1)
				P[i][j] = P[P[i][j - 1]][j - 1];
}

int query(int p, int q)
{
	int tmp, log, i;
	if (d[p] < d[q])
		tmp = p, p = q, q = tmp;
	for (log = 1; 1 << log <= d[p]; log++);
	log--;
	for (i = log; i >= 0; i--)
		if (d[p] - (1 << i) >= d[q])
			p = P[p][i];
	if (p == q)
		return p;
	for (i = log; i >= 0; i--)
		if (P[p][i] != -1 && P[p][i] != P[q][i])
			p = P[p][i], q = P[q][i];
	return P[p][0];
}

int dist(int u , int  v)
{
    int l =query( u , v);
    return ( d[u] + d[v] - 2 * d[l] );
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

	int  m , q; cin >> n >> m >> q;

	init_bridge_tree();
	for(int i = 0; i < m ; i++)
	{
		int u , v; cin >> u >> v;
		u--; v--;
		G[u].pb(v);
		G[v].pb(u);
	}

	make_set();
	make_tree();
	process3();
	dfs1(find_set(0));

	while(q--)
	{
		int a , b; cin >> a >> b;  
		a--; b--;
		int pi = find_set(a);
		int pj = find_set(b);
		if(pi == pj )
		{
			cout << "0" << "\n";  
		}
		else
		{
			cout << dist(pi,pj) << "\n";  
		}
	}
	return 0;
}

