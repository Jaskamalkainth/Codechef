/*
 *    J1K7_7
 *
 *    You can use my contents on a Creative Commons - Attribution 4.0 International - CC BY 4.0 License.  XD 
 *    - JASKAMAL KAINTH
 */
/*
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
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define left(x)		   (x << 1)
#define right(x) 	   (x << 1) + 1
#define mid(l, r) 	   ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	   {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		   memset(x,0,sizeof(x))

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

const int maxn = 1e3+7;
const int maxm = 1e3+7;
int sum[maxn][maxm];
int inp[maxn][maxm];
int n , m;
int lg[maxn] , p2[maxn];



const int maxlog = 15;
int table[maxlog][maxlog][maxn][maxm];
inline void BUILD_twoDimension_RMQ()
{
	// table[jr][ir][jc][ic] contains the minimum element from column ic -> ic + 2^jc - 1 of all rows [ir,ir+2^jr-1]
	 
	for(int ir = 0; ir < n; ir++)
		for(int ic = 0; ic < m; ic++)
			table[0][0][ir][ic] = inp[ir][ic];
	// jr = 0 so 1D RMQ for every row.
	for(int ir = 0; ir < n; ir++)
		for(int jc = 1; jc <= lg[m]; jc++)
			for(int ic = 0; ic + (1 << (jc-1)) < m; ic++)
				table[0][jc][ir][ic] = max(table[0][jc-1][ir][ic] , table[0][jc-1][ir][ic + p2[jc-1]]);  
	
	for(int jr = 1; jr <= lg[n]; jr++)
		for(int ir = 0; ir < n; ir++)
			for(int jc = 0; jc <= lg[m]; jc++)
				for(int ic = 0; ic < m; ic++)
					table[jr][jc][ir][ic] = max(table[jr-1][jc][ir][ic] , table[jr-1][jc][ir+ p2[jr-1]][ic]);  
}

inline int QUERY_twoDimension_RMQ(int x1,int y1 , int x2 , int y2)
{
	int lenx = x2-x1+1;
	int leny = y2-y1+1;
	int kx = lg[lenx];
	int ky = lg[leny];
	// Range R1 [x1,x1+2^kx-1] 
	// Range R2 [x2-2^kx+1,x2]
	// may overlap but since we  need min its fine.
	int min_Range1 = max(table[kx][ky][x1][y1] , table[kx][ky][x1][y2+1-p2[ky]]);
	int min_Range2 = max(table[kx][ky][x2+1-p2[kx]][y1] , table[kx][ky][x2+1-p2[kx]][y2+1-p2[ky]]);

	return max(min_Range1,min_Range2);
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 2; i < maxn; i++)
		lg[i] = lg[i/2] + 1;
	for(int i = 0; i < maxn; i++)
		p2[i] = (1<<i);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			cin >> inp[i][j];
			sum[i][j] = inp[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}

	BUILD_twoDimension_RMQ();

	int q; cin >> q;
	while(q--)
	{
		int a , b; cin >> a >> b;
		ll ans = OO;
		for(int i = 0; i+a <= n; i++)
		{
			for(int j = 0; j+b <= m; j++)
			{
				int query_val_max = QUERY_twoDimension_RMQ(i,j,i+a-1,j+b-1);
				int sum_range = sum[i+a-1][j+b-1] - sum[i+a-1][j-1] - sum[i-1][j+b-1] + sum[i-1][j-1];
				ans = min(ans , 1ll*a*b*query_val_max - sum_range);
			}
		}
		cout << ans << "\n";
	}
    return 0;
}

