#include <bits/stdc++.h>
using namespace std;

// Function to encrypt using Double Transposition
string doubleTranspositionEncrypt(string plain, string key1, string key2) {
    // First Transposition
    int col1 = key1.size();
    int row1 = plain.size() / col1;
    if (plain.size() % col1) row1++;  // Add extra row if required

    // Create the table for first transposition
    char table1[row1][col1];
    int k = 0;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            if (k < plain.size()) {
                table1[i][j] = plain[k];
                k++;
            } else {
                table1[i][j] = '*';  // Fill remaining positions with '*'
            }
        }
    }

    // Perform the first transposition based on key1
    map<char, int> mp1;
    for (int i = 0; i < key1.size(); i++) {
        mp1[key1[i]] = i + 1;
    }

    string sortedKey1 = key1;
    sort(sortedKey1.begin(), sortedKey1.end());

    vector<int> order1;
    for (int i = 0; i < sortedKey1.size(); i++) {
        order1.push_back(mp1[sortedKey1[i]]);
    }

    string firstTransposition = "";
    for (auto it : order1) {
        for (int i = 0; i < row1; i++) {
            firstTransposition += table1[i][it - 1];
        }
    }

    // Second Transposition
    int col2 = key2.size();
    int row2 = firstTransposition.size() / col2;
    if (firstTransposition.size() % col2) row2++;  // Add extra row if required

    // Create the table for second transposition
    char table2[row2][col2];
    k = 0;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            if (k < firstTransposition.size()) {
                table2[i][j] = firstTransposition[k];
                k++;
            } else {
                table2[i][j] = '*';  // Fill remaining positions with '*'
            }
        }
    }

    // Perform the second transposition based on key2
    map<char, int> mp2;
    for (int i = 0; i < key2.size(); i++) {
        mp2[key2[i]] = i + 1;
    }

    string sortedKey2 = key2;
    sort(sortedKey2.begin(), sortedKey2.end());

    vector<int> order2;
    for (int i = 0; i < sortedKey2.size(); i++) {
        order2.push_back(mp2[sortedKey2[i]]);
    }

    string cipher = "";
    for (auto it : order2) {
        for (int i = 0; i < row2; i++) {
            cipher += table2[i][it - 1];
        }
    }

    return cipher;
}

// Function to decrypt using Double Transposition
string doubleTranspositionDecrypt(string cipher, string key1, string key2) {
    // First, apply the second transposition decryption using key2
    int col2 = key2.size();
    int row2 = cipher.size() / col2;
    if (cipher.size() % col2) row2++;  // Add extra row if required

    char table2[row2][col2];
    int k = 0;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            if (k < cipher.size()) {
                table2[i][j] = cipher[k];
                k++;
            } else {
                table2[i][j] = '*';  // Fill remaining positions with '*'
            }
        }
    }

    // Create the key order for key2
    map<char, int> mp2;
    for (int i = 0; i < key2.size(); i++) {
        mp2[key2[i]] = i + 1;
    }

    string sortedKey2 = key2;
    sort(sortedKey2.begin(), sortedKey2.end());

    vector<int> order2;
    for (int i = 0; i < sortedKey2.size(); i++) {
        order2.push_back(mp2[sortedKey2[i]]);
    }

    // Generate the intermediate text after the second transposition
    string intermediate = "";
    for (auto it : order2) {
        for (int i = 0; i < row2; i++) {
            intermediate += table2[i][it - 1];
        }
    }

    // Now, apply the first transposition decryption using key1 on the intermediate result
    int col1 = key1.size();
    int row1 = intermediate.size() / col1;
    if (intermediate.size() % col1) row1++;  // Add extra row if required

    char table1[row1][col1];
    k = 0;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            if (k < intermediate.size()) {
                table1[i][j] = intermediate[k];
                k++;
            } else {
                table1[i][j] = '*';  // Fill remaining positions with '*'
            }
        }
    }

    // Create the key order for key1
    map<char, int> mp1;
    for (int i = 0; i < key1.size(); i++) {
        mp1[key1[i]] = i + 1;
    }

    string sortedKey1 = key1;
    sort(sortedKey1.begin(), sortedKey1.end());

    vector<int> order1;
    for (int i = 0; i < sortedKey1.size(); i++) {
        order1.push_back(mp1[sortedKey1[i]]);
    }

    // Generate the final decrypted text
    string decrypted = "";
    for (auto it : order1) {
        for (int i = 0; i < row1; i++) {
            decrypted += table1[i][it - 1];
        }
    }

    return decrypted;
}

int main() {
    string plain, key1, key2;
    cout << "Enter the message: ";
    getline(cin, plain);  // Read the plain text message
    cout << "Enter the first key: ";
    cin >> key1;  // Read the first key
    cout << "Enter the second key: ";
    cin >> key2;  // Read the second key

    string encrypted = doubleTranspositionEncrypt(plain, key1, key2);  // Encrypt the message
    cout << "Encrypted Message: " << encrypted << endl;

    string decrypted = doubleTranspositionDecrypt(encrypted, key1, key2);  // Decrypt the message
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}

