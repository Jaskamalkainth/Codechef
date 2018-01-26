#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t; 
    scanf("%d",&t);
    while(t--)
    {
        vector<int> a(4);
        for(int i = 0; i < 4; i++)
            scanf("%d",&a[i]);

        sort(a.begin(),a.end());
        if(a[0] == a[1] && a[2] == a[3])
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
