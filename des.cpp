#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Initial Permutation (IP)
const int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7};

// Inverse Initial Permutation (IP^(-1))
const int IIP[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                     39, 7, 47, 15, 55, 23, 63, 31,
                     38, 6, 46, 14, 54, 22, 62, 30,
                     37, 5, 45, 13, 53, 21, 61, 29,
                     36, 4, 44, 12, 52, 20, 60, 28,
                     35, 3, 43, 11, 51, 19, 59, 27,
                     34, 2, 42, 10, 50, 18, 58, 26,
                     33, 1, 41, 9, 49, 17, 57, 25};

// Expansion Permutation (E)
const int EP[48] = {32, 1, 2, 3, 4, 5,
                    4, 5, 6, 7, 8, 9,
                    8, 9, 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25,
                    24, 25, 26, 27, 28, 29,
                    28, 29, 30, 31, 32, 1};

// Permutation Function (P)
const int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
                   1, 15, 23, 26, 5, 18, 31, 10,
                   2, 8, 24, 14, 32, 27, 3, 9,
                   19, 13, 30, 6, 22, 11, 4, 25};

// S-box Table
int s_box[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

const int shift_table[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const int PC_1[56] = {57, 49, 41, 33, 25, 17, 9,
                      1, 58, 50, 42, 34, 26, 18,
                      10, 2, 59, 51, 43, 35, 27,
                      19, 11, 3, 60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15,
                      7, 62, 54, 46, 38, 30, 22,
                      14, 6, 61, 53, 45, 37, 29,
                      21, 13, 5, 28, 20, 12, 4};

const int PC_2[48] = {14, 17, 11, 24, 1, 5,
                      3, 28, 15, 6, 21, 10,
                      23, 19, 12, 4, 26, 8,
                      16, 7, 27, 20, 13, 2,
                      41, 52, 31, 37, 47, 55,
                      30, 40, 51, 45, 33, 48,
                      44, 49, 39, 56, 34, 53,
                      46, 42, 50, 36, 29, 32};

// Function to convert hexadecimal to binary
string hex_to_bin(const string &hex)
{
    unordered_map<char, string> mp = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

    string bin;
    for (char c : hex)
    {
        bin += mp[toupper(c)];
    }

    // Pad to 64 bits if necessary
    while (bin.length() < 64)
    {
        bin = "0" + bin;
    }

    return bin;
}

// Function to convert binary to hexadecimal
string bin_to_hex(const string &bin)
{
    unordered_map<string, string> mp = {
        {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"}, {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"}, {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"}, {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}};

    string hex;
    for (size_t i = 0; i < bin.length(); i += 4)
    {
        string chunk = bin.substr(i, 4);
        hex += mp[chunk];
    }
    return hex;
}

// Function to convert string to hexadecimal
string string_to_hex(const string &input)
{
    stringstream ss;
    ss << hex << setfill('0');
    for (char c : input)
    {
        ss << setw(2) << static_cast<int>(static_cast<unsigned char>(c));
    }
    return ss.str();
}

// Function to convert hexadecimal to string
string hex_to_string(const string &hex)
{
    string result;
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        string byte = hex.substr(i, 2);
        char chr = static_cast<char>(stoi(byte, nullptr, 16));
        result.push_back(chr);
    }
    return result;
}

// Function to perform XOR operation
string XOR(const string &s1, const string &s2)
{
    string result;
    for (size_t i = 0; i < s1.length(); i++)
    {
        result += (s1[i] == s2[i]) ? '0' : '1';
    }
    return result;
}

// Function to apply S-box transformation
string apply_s_box(const string &input)
{
    string output;
    for (int i = 0; i < 8; i++)
    {
        string chunk = input.substr(i * 6, 6);
        int row = (chunk[0] - '0') * 2 + (chunk[5] - '0');
        int col = (chunk[1] - '0') * 8 + (chunk[2] - '0') * 4 +
                  (chunk[3] - '0') * 2 + (chunk[4] - '0');
        int val = s_box[i][row][col];

        // Convert to 4-bit binary
        string bin;
        for (int j = 3; j >= 0; j--)
        {
            bin = ((val >> j) & 1 ? '1' : '0') + bin;
        }
        output += bin;
    }
    return output;
}

// Function to apply permutation
string apply_permutation(const string &input, const int *table, int size)
{
    string output;
    for (int i = 0; i < size; i++)
    {
        output += input[table[i] - 1];
    }
    return output;
}

// Function to generate subkeys
vector<string> generate_subkeys(const string &key)
{
    vector<string> subkeys;
    string permuted_key = apply_permutation(key, PC_1, 56);

    string left = permuted_key.substr(0, 28);
    string right = permuted_key.substr(28, 28);

    for (int i = 0; i < 16; i++)
    {
        // Perform left circular shift
        left = left.substr(shift_table[i]) + left.substr(0, shift_table[i]);
        right = right.substr(shift_table[i]) + right.substr(0, shift_table[i]);

        string combined = left + right;
        string subkey = apply_permutation(combined, PC_2, 48);
        subkeys.push_back(subkey);
    }

    return subkeys;
}

// Function to perform one round of DES
string des_round(const string &input, const string &subkey)
{
    string expanded = apply_permutation(input.substr(32), EP, 48);
    string xored = XOR(expanded, subkey);
    string substituted = apply_s_box(xored);
    string permuted = apply_permutation(substituted, P, 32);
    string result = XOR(input.substr(0, 32), permuted);
    return input.substr(32) + result;
}
// Main DES function
string des(string input, string key, bool decrypt = false)
{
    // Convert input to binary
    string binary_input = hex_to_bin(input);
    string binary_key = hex_to_bin(key);

    // Generate subkeys
    vector<string> subkeys = generate_subkeys(binary_key);
    if (decrypt)
    {
        reverse(subkeys.begin(), subkeys.end());
    }

    // Initial permutation
    string permuted = apply_permutation(binary_input, IP, 64);

    // 16 rounds of DES
    string current = permuted;
    for (const string &subkey : subkeys)
    {
        current = des_round(current, subkey);
    }

    // Swap last left and right halves
    current = current.substr(32) + current.substr(0, 32);

    // Final permutation
    string result = apply_permutation(current, IIP, 64);

    // Convert back to hexadecimal
    return bin_to_hex(result);
}

// Process function to handle multiple blocks
string process_des(const string &input, const string &key, bool decrypt = false)
{
    string processed;
    string working_input;

    if (decrypt)
    {
        working_input = input;
    }
    else
    {
        working_input = string_to_hex(input);
    }

    // Pad input if necessary
    while (working_input.length() % 16 != 0)
    {
        working_input += "0";
    }

    // Process each 64-bit (16 hex characters) block
    for (size_t i = 0; i < working_input.length(); i += 16)
    {
        string block = working_input.substr(i, 16);
        string processed_block = des(block, key, decrypt);
        processed += processed_block;
    }

    if (decrypt)
    {
        return hex_to_string(processed);
    }
    return processed;
}

int main()
{
    string choice, input, key;

   // cout << "Enter E for encryption or D for decryption: ";
    getline(cin, choice);

   // cout << "Enter the key (16 hexadecimal characters): ";
    getline(cin, key);

    // Validate key length
    if (key.length() != 16)
    {
        cout << "Error: Key must be exactly 16 hexadecimal characters." << endl;
        return 1;
    }

   // cout << "Enter the " << (choice == "E" ? "text to encrypt: " : "hexadecimal to decrypt: ");
    getline(cin, input);

    bool decrypt = (choice == "D");
    string result = process_des(input, key, decrypt);

    cout << "Result: " << result << endl;

    return 0;
}
