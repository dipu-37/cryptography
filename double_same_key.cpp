#include <bits/stdc++.h>
using namespace std;

// Function to perform the transposition based on key
void transpose(vector<vector<char>>& table, int row, int col, string key, bool reverse = false) {
    // Create a vector of pairs to store the key characters and their original indices
    vector<pair<char, int>> keyIndices;
    for (int i = 0; i < key.size(); i++) {
        keyIndices.push_back({key[i], i});
    }

    // Sort the keyIndices based on the key characters
    sort(keyIndices.begin(), keyIndices.end());

    // Determine the column order based on the sorted key
    vector<int> order(col);
    for (int i = 0; i < col; i++) {
        order[i] = keyIndices[i].second;
    }

    // If reversing, we need to invert the order
    if (reverse) {
        vector<int> invertedOrder(col);
        for (int i = 0; i < col; i++) {
            invertedOrder[order[i]] = i;
        }
        order = invertedOrder;
    }

    // Create a temporary table to store the transposed data
    vector<vector<char>> tempTable(row, vector<char>(col, '*'));

    // Transpose columns based on the order
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            tempTable[j][i] = table[j][order[i]];
        }
    }

    table = tempTable;  // Copy the transposed table back
}

// Function to encrypt the message
string encrypt(string plain, string key) {
    int col = key.size();
    int l = plain.size();
    int row = (l + col - 1) / col;  // Calculate number of rows, add extra row if needed

    // Create the table for encryption
    vector<vector<char>> table(row, vector<char>(col, '*'));
    int k = 0;

    // Fill the table row by row with the plain text
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (k < plain.size()) {
                table[i][j] = plain[k++];
            }
        }
    }

    // Perform the first transposition
    transpose(table, row, col, key);

    // Perform the second transposition (double transposition)
    transpose(table, row, col, key);

    // Generate cipher text from the transposed table
    string cipher = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (table[i][j] != '*') {  // Ignore padding characters in ciphertext
                cipher += table[i][j];
            }
        }
    }

    return cipher;
}

// Function to decrypt the message
string decrypt(string cipher, string key) {
    int col = key.size();
    int l = cipher.size();
    int row = (l + col - 1) / col;  // Calculate number of rows, add extra row if needed

    // Create the table for decryption
    vector<vector<char>> table(row, vector<char>(col, '*'));
    int k = 0;

    // Fill the table with cipher text
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (k < cipher.size()) {
                table[i][j] = cipher[k++];
            }
        }
    }

    // Perform the second transposition (reverse process)
    transpose(table, row, col, key, true);

    // Perform the first transposition (reverse process)
    transpose(table, row, col, key, true);

    // Generate decrypted text from the table
    string decrypted = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (table[i][j] != '*') {  // Ignore padding characters
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

    // Encrypt the message
    string encrypted = encrypt(plain, key);
    cout << "Encrypted Message: " << encrypted << endl;

    // Decrypt the message
    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
