#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;  scanf("%d",&n);
        vector<vector<ll>> arr(n);
        for(int i = 0; i < n; i++)
            arr[i].resize(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%lld",&arr[i][j]);
        ll  ans = *max_element(arr[n-1].begin(),arr[n-1].end());
        ll last_ele = ans;
        int flag = 1;
        for(int i = n-2; i >= 0; i--)
        {
            ll tans = 0ll;
            for(int j = 0; j < n; j++)
                if(arr[i][j] < last_ele)
                    tans = max(tans,arr[i][j]);
            ans += tans;
            last_ele = tans;
            if(!tans)
            {
                flag = 0;
                printf("%d\n",-1);
                break;
            }
        }
        if(flag)
            printf("%lld\n",ans);
    }
    return 0;
}
