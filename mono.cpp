#include<bits/stdc++.h>
using namespace std;
unordered_map<char,char>encrypt_map;
unordered_map<char,char>decrypt_map;
generate_key(string key)
{
    string alp="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0;i<26;i++)
    {
        encrypt_map[alp[i]]=key[i];
        decrypt_map[key[i]]=alp[i];
    }
}
string encryption(string pText)
{
    string cipherText="";
    for(char ch : pText)
    {
        if(isalpha(ch))
        {
            char upperchar = toupper(ch);
            char encryptedchar=encrypt_map[upperchar];
            cipherText+=(isupper(ch))?encryptedchar : tolower(encryptedchar);
        }
        else{
            cipherText += ch;
        }
    }

    return cipherText;

}

string decryption(string cipherText)
{
    string plainText="";
    for(char ch : cipherText)
    {
        if(isalpha(ch))
        {
            char upperchar = toupper(ch);
            char encryptedchar=decrypt_map[upperchar];
            plainText+=(isupper(ch))?encryptedchar : tolower(encryptedchar);
        }
        else{
            plainText += ch;
        }
    }

    return plainText;

}

int main()
{
    string pText;
    getline(cin,pText);
    string key="QWERTYUIOPLKJHGFDSAZXCVBNM";
    //cin>>key;

    generate_key(key);

    string cipherText= encryption(pText);
    cout<<cipherText<<endl;
    string plainText = decryption(cipherText);
    cout<<plainText<<endl;

}
