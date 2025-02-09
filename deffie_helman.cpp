
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll getExp(int base, ll exp, ll mod)
{
    if(exp==0) return 1;
    if(exp%2==0)
    {
        auto temp = getExp(base,exp/2,mod)%mod;
        return (temp*temp)%mod;
    }
    else{
        return (base*getExp(base,exp-1,mod)%mod)%mod;
    }

}
int main()
{
    ll x,y,g,p;
    cin>>p>>g>>x>>y;  //11 7 3 5

    ll A=getExp(g,x,p);
    ll B= getExp(g,y,p);
    cout<<A<<" "<<B<<endl;

    ll C=getExp(B,x,p);
    ll D=getExp(A,y,p);
    cout<<C<<" "<<D<<endl;

    if(C==D)
        cout<<"key Exchange Successful"<<endl;
    else
        cout<<"Key Exchange Failed"<<endl;

}

