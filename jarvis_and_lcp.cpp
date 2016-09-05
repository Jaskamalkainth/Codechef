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



const int MAXN = 5e6+6;

int len;
int iSA[MAXN], SA[MAXN];
int cnt[MAXN], next_gen[MAXN], lcp[ MAXN ], LCP[MAXN][22]; //internal
bool bh[MAXN], b2h[MAXN],m_arr[MAXN];

string s;
bool smaller_first_char(int a, int b){
	return s[a] < s[b];
}

void SuffixSort(int n) {
	for (int i=0; i<n; ++i){
		SA[i] = i;
	}
	sort(SA, SA + n, smaller_first_char);
	for (int i=0; i<n; ++i){
		bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
		b2h[i] = false;
	}
	for (int h = 1; h < n; h <<= 1){
		int buckets = 0;
		for (int i=0, j; i < n; i = j){
			j = i + 1;
			while (j < n && !bh[j]) j++;
			next_gen[i] = j;
			buckets++;
		}
		if (buckets == n) break;
		for (int i = 0; i < n; i = next_gen[i]){
			cnt[i] = 0;
			for (int j = i; j < next_gen[i]; ++j){
				iSA[SA[j]] = i;
			}
		}
		cnt[iSA[n - h]]++;
		b2h[iSA[n - h]] = true;
		for (int i = 0; i < n; i = next_gen[i]){
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
		for (int i=0; i<n; ++i){
			SA[iSA[i]] = i;
			bh[i] |= b2h[i];
		}
	}
	for (int i=0; i<n; ++i){
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
	InitLCP( len );
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
int lindx[MAXN];
vector<string> inp;
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
	len = s.length();
	SuffixSort(s.length());
	ConstructLCP();
	// Construct the Suffix Array of string s.
	int q; cin >> q;
	while(q--)
	{
		int i , j ;cin >>i  >> j;
		i--;j--;

		int si_idx = iSA[lindx[i]]; // position of the suffix which has ith string as prefix
		int sj_idx = iSA[lindx[j]]; // position of the suffix which has jth string as prefix

		int L = GetLCP(si_idx,sj_idx);
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
			if(GetLCP(mid,si_idx) < L)
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
		int high2 = len-1;
		while(low2 <= high2)
		{
			int mid = mid(low2,high2);
			if(GetLCP(mid,sj_idx) < L)
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

