#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to get the determinant of a 2x2 matrix
int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}

// Function to find modular inverse of determinant modulo 26
int modInverse(int det, int mod) {
    det = det % mod;
    for (int x = 1; x < mod; x++) {
        if ((det * x) % mod == 1)
            return x;
    }
    return -1;
}

// Function to encrypt text using Hill Cipher
string encrypt(string text, int key[2][2]) {
    string cipher = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        int x = text[i] - 'A';
        int y = text[i + 1] - 'A';
        cipher += (char)(((key[0][0] * x + key[0][1] * y) % 26) + 'A');
        cipher += (char)(((key[1][0] * x + key[1][1] * y) % 26) + 'A');
    }
    return cipher;
}

// Function to decrypt text using Hill Cipher
string decrypt(string cipher, int key[2][2]) {
    string text = "";
    int det = determinant(key);
    int detInv = modInverse(det, 26);

    if (detInv == -1) {
        cout << "Key matrix is not invertible. Decryption is not possible." << endl;
        return "";
    }

    // Adjoint (inverse of key matrix modulo 26)
    int adj[2][2] = { { key[1][1], -key[0][1] }, { -key[1][0], key[0][0] } };

    // Taking mod 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            adj[i][j] = ((adj[i][j] * detInv) % 26 + 26) % 26;
        }
    }

    for (size_t i = 0; i < cipher.length(); i += 2) {
        int x = cipher[i] - 'A';
        int y = cipher[i + 1] - 'A';
        text += (char)(((adj[0][0] * x + adj[0][1] * y) % 26) + 'A');
        text += (char)(((adj[1][0] * x + adj[1][1] * y) % 26) + 'A');
    }
    return text;
}

int main() {
    int key[2][2] = {{3, 3}, {2, 5}}; // Example key matrix
    string plaintext;
    cout << "Enter a plaintext (uppercase, even length): ";
    cin >> plaintext;

    string encrypted = encrypt(plaintext, key);
    cout << "Encrypted text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}

