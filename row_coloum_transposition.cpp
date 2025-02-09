#include<bits/stdc++.h>
using namespace std;

// Function to encrypt the message
string encrypt(string plain, string key) {
    int col = key.size();
    int l = plain.size();
    int row = l / col;
    if (l % col) row++;  // Add extra row if required

    // Create the table for encryption
    char table[row][col];
    int k = 0;

    // Fill the table row by row with the plain text
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (k < plain.size()) {
                table[i][j] = plain[k];
                k++;
            } else {
                table[i][j] = '*';  // Fill remaining positions with '*'
            }
        }
    }

    // Print the table for debugging
    cout << "Table for encryption:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << table[i][j];
        cout << endl;
    }

    // Create a map to store key order
    map<char, int> mp;
    for (int i = 0; i < key.size(); i++) {
        mp[key[i]] = i + 1;
    }

    // Sort the key
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

    // Create the order vector based on the sorted key
    vector<int> v;
    for (int i = 0; i < sortedKey.size(); i++) {
        v.push_back(mp[sortedKey[i]]);
    }

    // Generate cipher text based on the sorted key order
    string cipher = "";
    for (auto it : v) {
        for (int i = 0; i < row; i++) {
            cipher += table[i][it - 1];  // Collect column-wise
        }
    }
    return cipher;
}

// Function to decrypt the message
string decrypt(string cipher, string key) {
    int col = key.size();
    int l = cipher.size();
    int row = l / col;

    // Create the table for decryption
    char table[row][col];
    int k = 0;

    // Create a map to store key order
    map<char, int> mp;
    for (int i = 0; i < key.size(); i++) {
        mp[key[i]] = i + 1;
    }

    // Sort the key
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

    // Create the order vector based on the sorted key
    vector<int> v;
    for (int i = 0; i < sortedKey.size(); i++) {
        v.push_back(mp[sortedKey[i]]);
    }

    // Fill the table column by column with cipher text
    for (auto it : v) {
        for (int i = 0; i < row; i++) {
            table[i][it - 1] = cipher[k];
            k++;
        }
    }

    // Create the decrypted text by reading the table row by row
    string decrypted = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (table[i][j] != '*') {  // Ignore '*' characters
                decrypted += table[i][j];
            }
        }
    }
    return decrypted;
}

int main() {
    string plain, key;
    cout << "Enter the message: ";
    getline(cin, plain);  // Read the plain text message
    cout << "Enter the key: ";
    cin >> key;  // Read the key

    string encrypted = encrypt(plain, key);  // Encrypt the message
    cout << "Encrypted Message: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);  // Decrypt the message
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
