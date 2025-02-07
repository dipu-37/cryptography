#include <bits/stdc++.h>
using namespace std;

int main()
{
    string plain;
    cin >> plain;

    int depth;
    cin >> depth;

    int n = plain.size();
    char temp[depth][n];


    for(int i =0;i<depth; i++)
    {
        for (int j=0; j<n; j++)
        {
            temp[i][j] = '.';
        }
    }

    int r = 0;
    bool flag = false;


    for(int i=0; i<n; i++)
    {
        temp[r][i] = plain[i];
        if (r == depth - 1)
            flag = false;
        else if (r == 0)
            flag = true;

        if (flag)
            r++;
        else
            r--;
    }

    for(int i=0;i<depth; i++)
    {
        for (int j=0;j<n; j++)
        {
            cout<<temp[i][j];
        }
        cout<<endl;
    }

    string cipher="";
    for(int i=0;i<depth; i++)
    {
        for (int j=0;j<n; j++)
        {
            if(temp[i][j]=='.') continue;
            cipher+=temp[i][j];
        }

    }

    cout<<"cipher"<<cipher<<endl;


}
