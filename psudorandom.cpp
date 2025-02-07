#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,x0,m,n;
    cin>>a>>b>>x0>>m>>n;
    int random[n+1];
    random[0]=x0;
    for(int i=1;i<n;i++)
    {
        random[i]=(a*random[i-1]+b)%m;
    }

    for(int i=0;i<n;i++)
    {
        cout<<random[i]<<" ";
    }
}

