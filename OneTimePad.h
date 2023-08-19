#ifdef ONETIMEPAD_H
#define ONETIMEPAD_H

#include <string>
#include <vector> 

string readFile();
string toBinary(string text);
string generateKey(string binary);

string XORfunc(string binaryText, string key);
void emptyFile(string fileName);
void binaryToString(string cipherBinary, string fileName);




#endif