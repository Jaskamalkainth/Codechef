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
#define left(x)		       (x << 1)
#define right(x) 	   	   (x << 1) + 1
#define mid(l, r) 	   	   ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))

inline int nextint(){ int x; scanf("%d",&x);   return x; }
inline ll  nextll() { ll  x; scanf("%lld",&x); return x; }

#define gc getchar
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}
// variadics
template<typename T >T min_ ( T a , T b ) { return a > b ? b : a ; }
template < typename T ,  typename... Ts > T min_( T first , Ts... last ){ return  min_(first, min_(last...)); }

// lambda exp auto  square = [](int inp) { return inp * inp; } ;

template<class T, class S> std::ostream& operator<<(std::ostream &os, const std::pair<T, S> &t) {
	os<<"("<<t.first<<", "<<t.second<<")";
	return os;
}
template<typename T> ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "["; size_t last = v.size() - 1; for(size_t i = 0; i < v.size(); ++i) {
    out << v[i]; if (i != last) out << ", "; } out << "]"; return out;
}

ll pwr(ll base, ll p, ll mod){
ll ans = 1; while(p) { if(p&1) ans=(ans*base)%mod; base=(base*base)%mod; p/=2; } return ans;
}
ll gcd(ll a, ll b) {  return b == 0 ? a : gcd(b,a%b); }
ll lcm(ll a, ll b) {  return a*(b/gcd(a,b)); }

const long double PI = (long double)(3.1415926535897932384626433832795);
const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();
const int mod = 1e9+7;
const int oo = 0x3f3f3f3f;
const ll  OO = 0x3f3f3f3f3f3f3f3fll;

const int maxn = 1e5+7;
vector<pair<int,int>> ticket[maxn];
vi G[maxn];
ll dp[maxn];
int n , m;
ll tree[4*maxn];

inline void update(int node ,int left ,int right ,int id, ll val)
{
	if(left > id || right < id)
		return;
	if(left >= id  && right <= id)
	{
		tree[node] = val;  
		return ;
	}
	int mid = mid(left,right);
	update(2*node,left,mid,id,val);
	update(2*node+1,mid+1,right,id,val);
	tree[node] = min(tree[2*node],tree[2*node+1]);
}
inline ll query(int node ,int left ,int right ,int lq ,int rq)
{
	if(left > rq || right < lq)
	{
		return OO;  
	}
	if(left >= lq && right <= rq)
	{
		return tree[node];  
	}
	int mid = mid(left,right);
	return min(query(2*node,left,mid,lq,rq),query(2*node+1,mid+1,right,lq,rq));
}
inline void dfs(int u , int h)
{
	for(auto t: ticket[u])
	{
		int k = t.ff;
		int w = t.ss;
		dp[u] = min(dp[u] , query(1,0,n,max(0,h-k),h) + w);
	}
	update(1,0,n,h,dp[u]);
	for(auto &v: G[u])
	{
		dfs(v,h+1);
	}
	update(1,0,n,h,OO);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 0; i < 4*maxn; i++)
		tree[i] = OO;
	for(int i = 0; i < maxn; i++)
		dp[i] = OO;
	for(int i = 1; i <= n-1; i++)
	{
		int u , v; cin >> u >> v;
		G[v].pb(u);
	}
	for(int i = 1; i <= m; i++)
	{
		int v, k ,w; cin >> v >> k >> w;
		ticket[v].pb({k,w});
	}
	dp[1] = 0;
	update(1,0,n,0,0);
	dfs(1,0);
	int q; cin >> q;
	while(q--)
	{
		int h; cin >> h;
		cout << dp[h] << "\n";
	}
	return 0;
}

