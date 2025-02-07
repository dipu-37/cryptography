#include <bits/stdc++.h>
using namespace std;

string keyGeneration(string pText, string key)
{
    string newKey = key;
    while (newKey.size() < pText.size())
    {
        newKey += key;
    }
    newKey = newKey.substr(0, pText.size());

    cout << "Generated Key: " << newKey << endl;

    return newKey;
}

// Encryption Function
string encryption(string pText, string key)
{
    string cipherText = "";
    key = keyGeneration(pText, key);

    for (int i = 0; i < pText.size(); i++)
    {
        if (isalpha(pText[i]))
        {
            char base = isupper(pText[i]) ? 'A' : 'a';
            cipherText += (pText[i] - base + (toupper(key[i]) - 'A')) % 26 + base;
        }
        else
        {
            cipherText += pText[i];
        }
    }
    return cipherText;
}

string decryption(string cipherText, string key)
{
    string plainText = "";
    key = keyGeneration(cipherText, key);

    for (int i = 0; i < cipherText.size(); i++)
    {
        if (isalpha(cipherText[i]))
        {
            char base = isupper(cipherText[i]) ? 'A' : 'a';
            plainText += (cipherText[i] - base - (toupper(key[i]) - 'A') + 26) % 26 + base;
        }
        else
        {
            plainText += cipherText[i];
        }
    }
    return plainText;
}

int main()
{
    string pText, key;
    cout << "Enter Plaintext: ";
    getline(cin, pText);
    cout << "Enter Key: ";
    cin >> key;

    // Convert key to uppercase for uniformity
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    string cipherText = encryption(pText, key);
    cout << "Encrypted Text: " << cipherText << endl;

    string decryptedText = decryption(cipherText, key);
    cout << "Decrypted Text: " << decryptedText << endl;


}
