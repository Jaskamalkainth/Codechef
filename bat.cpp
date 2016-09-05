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
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))

const int mod=1e9+7;

template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

#define gc getchar
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}
ll pwr(ll base, ll p, ll mod){
ll ans = 1;while(p){if(p&1)ans=(ans*base)%mod;base=(base*base)%mod;p/=2;}return ans;
}

const int maxn = 1e5+7;
bitset<11> b[1<<20][19];
int dep[maxn];
int col[maxn+1];
	  
int n;
int mx_dep = -1;
void dfs0(int u = 1, int d = 0)
{
	dep[u] = d;
	mx_dep = max(mx_dep , d);
	if( 2*u <= n )
	{
		dfs0(2*u, d+1);  
	}
	if( 2*u + 1 <= n )
	{
		dfs0(2*u+1, d+1);  
	}
}

void dfs(int u)
{
	b[u][0].set(col[u]);  
	if( 2*u <= n )
	{
		dfs(2*u);  
	}
	if( 2*u + 1 <= n )
	{
		dfs(2*u+1); 
	}
	for(int d = 1; d <= mx_dep-dep[u]; d++)
	{
		if(2*u+1 <= n)
			b[u][d] |= b[2*u+1][d-1] ;
		else
			b[u][d].reset();

		if(2*u <= n)
			b[u][d] |= b[2*u][d-1];
		else
			b[u][d].reset();

		b[u][d].set(col[u]);  
	}
}

int pre[1<<20][19];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t; cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> col[i];
		dfs0();
		dfs(1);
	
		int q; cin >> q;
		while(q--)
		{
			int u , k; cin >> u >> k;
			int low = 0;
			int high = mx_dep-dep[u];
			int ans = -1;
			while(low <= high)
			{
				int mid = mid(low,high);
				if(b[u][mid].count() >= k)
				{
					high = mid-1;
					ans = mid;
				}
				else
				{
					low = mid+1;  
				}
			}
			cout << ans << "\n";
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j < 19; j++)
			{
				b[i][j].reset();  
			}
		}
	}
    return 0;
}

