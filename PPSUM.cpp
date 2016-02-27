#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
int main()
{
	int t; cin >> t;
	while(t--)
	{
		ll n, d; cin >> d >> n;


		ll ans = 0ll;
		for(int i = 0; i < d; i++)
		{
			ll fans = (ll)(n*(n+1))/2;
			ans = fans;
			n = fans;
		}
		cout << ans << "\n";
	}
	return 0;
}
