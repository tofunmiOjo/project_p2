#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string fileName;

string readFile() {
    cout << "Enter the file name: ";
    cin >> fileName;

    ifstream myfile(fileName);
    string content;

    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            content += line;
        }
        myfile.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    return content;
}

void sendToFile(vector<unsigned char> ciphertext){
  ofstream myfile;
  myfile.open (fileName);

   for (int i = 0; i < ciphertext.size(); i++) {
  myfile << hex << (int) ciphertext[i];
}
  myfile.close();
}


// Initialize the RC4 key schedule with the given key
void init_rc4(vector<unsigned char>& key, vector<unsigned char>& s) {
    int key_length = key.size();
    int j = 0;

    // Initialize the S-box
    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }

    // Permute the S-box with the key
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key_length]) % 256;
        swap(s[i], s[j]);
    }
}

// Encrypt the plaintext using the RC4 key schedule
void rc4_encrypt(vector<unsigned char>& plaintext, vector<unsigned char>& key, vector<unsigned char>& ciphertext) {
    vector<unsigned char> s(256);
    init_rc4(key, s);

    int i = 0;
    int j = 0;

    // Generate the keystream and XOR it with the plaintext to get the ciphertext
    for (int k = 0; k < plaintext.size(); k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(s[i], s[j]);
        int t = (s[i] + s[j]) % 256;
        ciphertext.push_back(plaintext[k] ^ s[t]);
    }
}

// Decrypt the ciphertext using the RC4 key schedule
void rc4_decrypt(vector<unsigned char>& ciphertext, vector<unsigned char>& key, vector<unsigned char>& plaintext) {
    rc4_encrypt(ciphertext, key, plaintext);
}

int main() {
    // Example usage
    string plaintext_str = readFile();
    vector<unsigned char> plaintext(plaintext_str.begin(), plaintext_str.end());

    string key_str = "my secret key";
    vector<unsigned char> key(key_str.begin(), key_str.end());

    vector<unsigned char> ciphertext;
    rc4_encrypt(plaintext, key, ciphertext);

    vector<unsigned char> decrypted_plaintext;
    rc4_decrypt(ciphertext, key, decrypted_plaintext);

    sendToFile(ciphertext);

    cout << "Plaintext: " << plaintext_str << endl;
    cout << "Key: " << key_str << endl;
    cout << "Ciphertext: ";
    for (int i = 0; i < ciphertext.size(); i++) {
        cout << hex << (int) ciphertext[i];
    }
    cout << endl;

    string decrypted_plaintext_str(decrypted_plaintext.begin(), decrypted_plaintext.end());
    cout << "Decrypted plaintext: " << decrypted_plaintext_str << endl;


    return 0;
}
