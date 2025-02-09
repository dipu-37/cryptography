#include <bits/stdc++.h>
using namespace std;

char grid[5][5];
bool mark[26] = {false};
string key, text;

void createGrid(string key) {
    key += "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // J is merged with I
    int r = 0, c = 0;
    for (char ch : key) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';
        if (!mark[ch - 'A']) {
            mark[ch - 'A'] = true;
            grid[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }
}

void showGrid() {
    cout << "5x5 Key Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

pair<int, int> getPosition(char ch) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (grid[i][j] == ch)
                return {i, j};
    return {-1, -1};
}

string formatText(string text) {
    string result;
    for (char ch : text) {
        if (ch == ' ') continue;
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';
        result += ch;
    }
    for (size_t i = 0; i < result.length(); i += 2)
        if (i + 1 < result.length() && result[i] == result[i + 1])
            result.insert(i + 1, "X");
    if (result.length() % 2 != 0)
        result += 'X';
    return result;
}

string encrypt(string text) {
    text = formatText(text);
    string cipher;
    for (size_t i = 0; i < text.length(); i += 2) {
        auto [r1, c1] = getPosition(text[i]);
        auto [r2, c2] = getPosition(text[i + 1]);
        if (r1 == r2)
            cipher += grid[r1][(c1 + 1) % 5], cipher += grid[r2][(c2 + 1) % 5];
        else if (c1 == c2)
            cipher += grid[(r1 + 1) % 5][c1], cipher += grid[(r2 + 1) % 5][c2];
        else
            cipher += grid[r1][c2], cipher += grid[r2][c1];
    }
    return cipher;
}

string decrypt(string cipher) {
    string text;
    for (size_t i = 0; i < cipher.length(); i += 2) {
        auto [r1, c1] = getPosition(cipher[i]);
        auto [r2, c2] = getPosition(cipher[i + 1]);
        if (r1 == r2)
            text += grid[r1][(c1 + 4) % 5], text += grid[r2][(c2 + 4) % 5];
        else if (c1 == c2)
            text += grid[(r1 + 4) % 5][c1], text += grid[(r2 + 4) % 5][c2];
        else
            text += grid[r1][c2], text += grid[r2][c1];
    }
    return text;
}

int main() {
    cout << "Enter key: ";
    cin >> key;
    cout << "Enter text: ";
    cin >> text;
    createGrid(key);
    showGrid();
    string encrypted = encrypt(text);
    cout << "Encrypted: " << encrypted << endl;
    string decrypted = decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;
}
