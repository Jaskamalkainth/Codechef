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


const int maxn = 5e5+6;
int inp[maxn];
struct node
{
	ll val;
	ll ans;
	ll cnt_one;
	void merge(node &l , node &r)
	{
		cnt_one = l.cnt_one + r.cnt_one;
		ans = max(l.ans,r.ans);
	}
	node()
	{
		val = -1;
		ans = 1;
		cnt_one = 0;
	}
}tree[4*maxn];

const int maxN = 3e6+7;
int  pp[maxN+1];
vector <int> prime,sp;
inline void pre_sieve()
{
    sp.resize(maxN);
    for(ll i = 2; i < maxN; i++ )
        if( pp[i] == 0 )
        {
            sp[i] = i;
            for(ll j = i*i; j < maxN; j += i)
                if ( pp[j] == 0 )
                {
                    sp[j] = i;
                    pp[j] = 1;
                }
        }
}


inline void build(int id, int left , int right)
{
	if(left == right)
	{
		tree[id].val =  inp[left];
		tree[id].ans = sp[tree[id].val];
		if(tree[id].ans == 0)
			tree[id].ans = 1;
		tree[id].cnt_one = (inp[left] == 1) ? 1 : 0;
		return ;
	}
	int mid = mid(left,right);
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}
inline void range_upd(int id ,int left ,int right ,int lq ,int rq)
{
	if(left > rq || right < lq)
		return ;
	if(tree[id].cnt_one == (right-left+1))
		return ;
	if(left == right)
	{
		tree[id].val = tree[id].val/sp[tree[id].val];
		tree[id].ans = sp[tree[id].val];
		if(tree[id].ans == 0)
			tree[id].ans = 1;
		tree[id].cnt_one = (tree[id].val == 1) ? 1 : 0;
		return ;
	}
	int mid = mid(left,right);
	range_upd(2*id,left,mid,lq,rq);
	range_upd(2*id+1,mid+1,right,lq,rq);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}
inline node range_query(int id, int left ,int right ,int lq ,int rq)
{
	if(left > rq || right < lq)
		return node();
	if(left >= lq && right <= rq)
	{
		return tree[id];  
	}
	int mid = mid(left,right);
	node l_ = range_query(2*id,left,mid,lq,rq);
	node r_ = range_query(2*id+1,mid+1,right,lq,rq);

	node temp;
	temp.merge(l_,r_);
	return temp;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	pre_sieve();
	int t; cin >> t;
	while(t--)
	{
		int n , m; cin >> n >> m;
		for(int i = 0; i < n; i++)
			cin >> inp[i];
		build(1,0,n-1);
		while(m--)
		{
			int tp; cin >> tp;
			int l, r; cin >> l >> r;
			if(tp == 0)
			{
				range_upd(1,0,n-1,l-1,r-1);
			}
			else
			{
				cout << range_query(1,0,n-1,l-1,r-1).ans << " ";
			}
		}
		cout << "\n";
	}
    return 0;
}

