// This will create the encryption of the text file using the one time pad
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <cstdlib>
using namespace std;


// Will read the sending file
string readFile() {
    // Creating an object of fstream type
    fstream newfile;
    string total = "";

    // Opening the file and doing the read operation
    newfile.open("send.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        while(getline(newfile, tp)) {
            total += tp;
        }
    }
    newfile.close();
    return total;
}

// Will convert the read file into binary text (each character will be 8 bits and converted accordingly)
// Takes each character, converts it into a byte
// the byte is then added to the string
// Once everything in the file is done it then returns that binary string

string toBinary(string text) {
    string binaryString = "";
    for (char& _char: text) {
        binaryString += bitset<8>(_char).to_string();
    }
    return binaryString;
}

// Creating the pseudorandom key generation
string generateKey(string binary) {
    string key = "";

    for(int i = 0; i < binary.length(); i++) {

        if (i % 8 == 0) {
            key += "0";
        } else {
        int bit = rand() % 2;
        key += to_string(bit);
        }
    }
    return key;
}

// Creating an XOR function to encrypt the text being sent over
string XORfunc(string binaryText, string key) {

    string cipherText = "";
    for(int i = 0; i < binaryText.length(); i++) {

        if (binaryText[i] == '0' && key[i] == '0') {
            cipherText += "0";
        } else if (binaryText[i] == '1' && key[i] == '1') {
            cipherText += "0";
        } else {
            cipherText += "1";
        }
    }
    return cipherText;
}



// We will first empty the file that we are putting the text back into to
void emptyFile(string fileName) {
    ofstream ofs;
    ofs.open(fileName, ofstream::out | ofstream::trunc);
    ofs.close();
}



// Converting binary text back into characters
void binaryToString(string cipherBinary, string fileName) {
    string binaryString = cipherBinary;
    string outputText = "";

 
    for (int i = 0; i < cipherBinary.length(); i += 8) {
        bitset<8> bits(cipherBinary.substr(i, 8));
        char c = static_cast<char>(bits.to_ullong());
        outputText += c;
    }

    ofstream outputfile;
    outputfile.open(fileName);
    for(int i = 0; i < outputText.length(); i++) {
        outputfile.put(outputText[i]);
    }

}


int main() {


    cout << " enrypt or decrpty -- ";
    string choice;
    cin >> choice;

    if(choice == "e"){
    // Getting the text from the file
    string test = readFile();
    // cout << test << endl;

    // Converting that text into binary
    string binaryText = toBinary(test);
    //cout << binaryText << endl;

    // Generating the psuedorandom key
    string key = generateKey(binaryText);
    cout << key << endl;

    // XORing the key and the text
    string cipher = XORfunc(binaryText, key);
    //cout << cipher << endl;
    //cout << endl;

    // Now we are clearing the file
    //cout << "We are now clearing the file" << endl;
    emptyFile("send.txt");
    string test2 = readFile();
    //cout << test2 << endl;

    //cout << " We are now turning the XOR binary back into characters to place into the file" << endl;
    // Also placing the characters back into the file
    binaryToString(cipher, "send.txt");
    cout << endl;
    }

    else if(choice == "d"){

    // Getting the text from the file
    string test = readFile();
    // cout << test << endl;

    // Converting that text into binary
    string binaryText = toBinary(test);
    //cout << binaryText << endl;

    // Generating the psuedorandom key
    string key = generateKey(binaryText);
    cout << key << endl;

    // XORing the key and the text
    string cipher = XORfunc(binaryText, key);
    //cout << cipher << endl;
    //cout << endl;

    // Now we are clearing the file
    //cout << "We are now clearing the file" << endl;
    emptyFile("Recieved.txt");
    string test2 = readFile();
    //cout << test2 << endl;

    //cout << " We are now turning the XOR binary back into characters to place into the file" << endl;
    // Also placing the characters back into the file
    binaryToString(cipher, "Recieved.txt");
    cout << endl;
    }
    /*
    //cout << " Converting it back" << endl;
    string testAgain = readFile();
    //cout << testAgain << endl;

    string testTwo = toBinary(testAgain);
    cout << testTwo << endl;
    */
    return 0;
}
