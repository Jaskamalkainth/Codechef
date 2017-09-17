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
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define ff first
#define ss second
#define debug(x)	   {cerr <<#x<<" = " <<x<<"\n"; }

/*
    Suffix Arrays implementation
    O(n log n) - Manber and Myers algorithm
    Refer to "Suffix arrays: A new method for on-line texting searches", by Udi Manber and Gene Myers
 */
class suffixArray
{
public:
	string s;
	int len;
	vector<int> iSA,SA;
	vector<int> cnt,next_gen,lcp;
	vector<vector<int>> LCP;
	vector<bool> bh,b2h,m_arr;
	suffixArray(string sinp)
	{
		s = sinp;
		len = sinp.size();
		iSA.resize(len); SA.resize(len);
		cnt.resize(len); next_gen.resize(len); lcp.resize(len);
		LCP.resize(len);
		bh.resize(len); b2h.resize(len); m_arr.resize(len);
		for(int i = 0; i < len; i++)
			LCP[i].resize(22);
	}
	bool smaller_first_char(int a, int b){
		return s[a] < s[b];
	}
	void SuffixSort() {
		for (int i=0; i<len; ++i){
			SA[i] = i;
		}
		vector<pair<char,int> > arrr;
		for(int i = 0; i < len; i++)
			arrr.pb({s[SA[i]],SA[i]});
		sort(arrr.begin(),arrr.end());
		for(int i = 0; i < len; i++)
			SA[i] = arrr[i].ss;

		for (int i=0; i<len; ++i){
			bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
			b2h[i] = false;
		}
		for (int h = 1; h < len; h <<= 1){
			int buckets = 0;
			for (int i=0, j; i < len; i = j){
				j = i + 1;
				while (j < len && !bh[j]) j++;
				next_gen[i] = j;
				buckets++;
			}
			if (buckets == len) break;
			for (int i = 0; i < len; i = next_gen[i]){
				cnt[i] = 0;
				for (int j = i; j < next_gen[i]; ++j){
					iSA[SA[j]] = i;
				}
			}
			cnt[iSA[len - h]]++;
			b2h[iSA[len - h]] = true;
			for (int i = 0; i < len; i = next_gen[i]){
				for (int j = i; j < next_gen[i]; ++j){
					int s = SA[j] - h;
					if (s >= 0){
						int head = iSA[s];
						iSA[s] = head + cnt[head]++;
						b2h[iSA[s]] = true;
					}
				}
				for (int j = i; j < next_gen[i]; ++j){
					int s = SA[j] - h;
					if (s >= 0 && b2h[iSA[s]]){
						for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
					}
				}
			}
			for (int i=0; i<len; ++i){
				SA[iSA[i]] = i;
				bh[i] = bh[i] | b2h[i];
			}
		}
		for (int i=0; i<len; ++i){
			iSA[SA[i]] = i;
		}
	}
	void InitLCP(int n) {
		for (int i=0; i<n; ++i)
			iSA[SA[i]] = i;
		lcp[0] = 0;
		for (int i=0, h=0; i<n; ++i) {
			if (iSA[i] > 0) {
				int j = SA[iSA[i]-1];
				while (i + h < n && j + h < n && s[i+h] == s[j+h])
					h++;
				lcp[iSA[i]] = h;
				if (h > 0)
					h--;
			}
		}
	}
	void ConstructLCP() {
		InitLCP(len);
		for(int i = 0;i<len;++i)
			LCP[i][0] = lcp[i];
		for(int j = 1;(1<<j)<=len;++j){
			for(int i = 0;i+(1<<j)-1<len;++i){
				if(LCP[i][j-1]<=LCP[i+ ( 1<<(j-1) )][j-1])
					LCP[i][j] = LCP[i][j-1];
				else
					LCP[i][j] = LCP[i+(1<<(j-1))][j-1];
			}
		}
	}
	int GetLCP(int x, int y) {
		if(x == y) return len-SA[x];
		if(x > y) swap(x,y);
		int log = 0;
		while((1<<log)<=(y-x)) ++log;
		--log;
		return min(LCP[x+1][log],LCP[y-(1<<log)+1][log]);
	}

	/*string inp; cin >> inp;
    suffixArray sa1(inp);
    sa1.SuffixSort();
    sa1.ConstructLCP();*/
// isA[i] : rank array
// SA[i]  : Suffix array
// lcp[i] : lcp array
// GetLCP(i,j): lcp of any 2 suffixes.
};
const int MAXN = 5e6+6;
int lindx[MAXN];
vector<string> inp;
string s;
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

	int n; cin >> n;
	for(int i = 0; i < n; i++)
	{
		if(i)
			s += "$";
		int lenx = s.length();
		lindx[i] = lenx;
		string x; cin >> x;
		inp.pb(x);
		s += x;
	}
	s += "$";
	// Now our string s = becomes : s1$s2$s3...$sn$
    suffixArray sa(s);
    sa.SuffixSort();
	sa.ConstructLCP();
	// Construct the Suffix Array of string s.
	int q; cin >> q;
	while(q--)
	{
		int i , j ;cin >>i  >> j;
		i--;j--;

		int si_idx = sa.iSA[lindx[i]]; // position of the suffix which has ith string as prefix
		int sj_idx = sa.iSA[lindx[j]]; // position of the suffix which has jth string as prefix

		int L = sa.GetLCP(si_idx,sj_idx);
		int t = min(inp[i].length(),inp[j].length());
		L = min(t,L);
		// L is the LCP of ith and jth string.
		if(!L)
		{
			cout <<"0\n";  // If L = 0 then trivial
			continue;
		}
		if(si_idx > sj_idx)
			swap(si_idx,sj_idx);
		// Our starting range of suffixes which has prefix = LCP(i,j) is [lower_range,upper_range].
		// Now we want to expand this interval from both ends.
		// So we do Binary search for the index in the suffix array till which the prefix of the suffix has LCP >= L.
		//
		int low1 = 0;
		int high1 = si_idx;
		int lower_range = si_idx;
		int upper_range = sj_idx;

		while(low1 <= high1)
		{
			int mid = mid(low1,high1);
			if(sa.GetLCP(mid,si_idx) < L)
			{
				low1 = mid+1;  
			}
			else
			{
				high1 = mid-1;
				lower_range = min(mid,lower_range);
			}
		}
		int low2 = sj_idx;
		int high2 = sa.len-1;
		while(low2 <= high2)
		{
			int mid = mid(low2,high2);
			if(sa.GetLCP(mid,sj_idx) < L)
			{
				high2 = mid-1;
			}
			else
			{
				low2 = mid+1;
				upper_range = max(upper_range,mid);
			}
		}
		cout << upper_range-lower_range+1 << "\n";
	}
    return 0;
}

