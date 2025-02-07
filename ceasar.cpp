#include<bits/stdc++.h>
using namespace std;
string encryption(string s, int k)
{
    int n = s.size();
    for(int i=0; i<n; i++)
    {
        if(isalpha(s[i]))
        {
            //char base = isupper(s[i]) ? 'A' : 'a';
            int base = isupper(s[i])? 65 : 97;
            s[i]=(s[i]-base+k)%26+base;
        }

    }
    return s;

}
void decryption(string s, int k)
{
    int n = s.size();
    for(int i=0; i<n; i++)
    {
        if(isalpha(s[i]))
        {
            //char base = isupper(s[i]) ? 'A' : 'a';
            int base = isupper(s[i])? 65 : 97;
            s[i]=(s[i]-base-k)%26+base;
        }

    }
    cout<<"decryption: "<<s<<endl;
}
int main()
{
    string s;
    getline(cin,s);
    int k;
    cin>>k;

    string se= encryption(s,k);
    cout<<"encryption: "<<se<<endl;
    decryption(se,k);
}
