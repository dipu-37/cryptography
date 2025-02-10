
#include<bits/stdc++.h>
#define ll long long
using namespace std;

bool isPrime(ll n)
{
    for(ll i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}
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
    int a,b,x0,m;
    cin>>a>>b>>x0>>m;
    int random[100];
    random[0]=x0;
    vector<ll>prime;
    for(int i=1;i<100;i++)
    {
        ll ran = (a*random[i-1]+b)%m;
        if(isPrime(ran))
        {
            prime.push_back(ran);
        }

    }


    ll p=prime[0];
    ll q=prime[1];
    cout<<"two random number :"<<p<<" "<<q<<endl;

//    for(int i=0;i<n;i++)
//    {
//        cout<<random[i]<<" ";
//    }


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

    cout<<"enter a message "<<endl;
    ll M;
    cin>>M;
    ll c= getExp(M,e,n);
    cout<<"cipher : "<<c<<endl;
    ll me=getExp(c,d,n);
    cout<<"plain : "<<M<<endl;


}

