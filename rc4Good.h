#ifndef RC4GOOD_H
#define RC4GOOD_H


#include <string>
#include <vector>

std::string readFile();

void sendToFile(std::vector<unsigned char> ciphertext);

void init_rc4(std::vector<unsigned char>& key, std::vector<unsigned char>& s);

void rc4_encrypt(std::vector<unsigned char>& plaintext, std::vector<unsigned char>& key, std::vector<unsigned char>& ciphertext);

void rc4_decrypt(std::vector<unsigned char>& ciphertext, std::vector<unsigned char>& key, std::vector<unsigned char>& plaintext);

std::vector<unsigned char> getKey();

void sendKey(std::vector<unsigned char>& key);


extern std::string key_str;
extern std::vector<unsigned char> keyUpdate;




#endif



