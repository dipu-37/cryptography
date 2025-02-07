
#include<bits/stdc++.h>
#define ll long long
using namespace std;

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
    ll p,q;
    cin>>p>>q;
    ll n=p*q;
    ll phi = (p-1)*(q-1);
    ll e;
    for(ll i=2;i<phi; i++)
    {
        if(__gcd(i,phi)==1)
        {
            e=i;
            break;
        }
    }

    // private key generation
    ll d=0;
    while((d*e)%phi !=1)
    {
        d++;
    }

    cout<<"public key: "<<e<<" "<<n<<endl;
    cout<<"private key: "<<d<<" "<<n<<endl;

    cout<<"enter a message"<<endl;
    ll M;
    cin>>M;
    ll c= getExp(M,e,n);
    cout<<"cipher"<<c<<endl;
    ll m=getExp(c,d,n);
    cout<<"plain"<<m<<endl;


}
