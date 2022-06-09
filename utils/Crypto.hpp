#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/rand.h>
#include "../libs/aes256/AES.h"

using namespace std;

vector<unsigned char> randomIV(int iv_size) {
    vector<unsigned char> iv(iv_size);
    RAND_bytes(iv.data(), iv_size);
    return iv;
}

// kpad or kokosabzi pad is a custom padding scheme.
void kpad(vector<unsigned char> & data, int blockSize) {
    if (data.size() % blockSize != 0) {
        data.push_back(0x80);
        if (data.size() % blockSize != 0) {
            while (data.size() % blockSize != 0) {
                data.push_back(0x00);
            }
        }
    }
}

// kunpad or kokosabzi unpad is a custom unpadding scheme.
void kunpad(vector<unsigned char> & data, int blockSize) {
    while (data.back() == 0x00) {
        data.pop_back();
    }
    if (data.back() == 0x80) {
        data.pop_back();
    }
}

bool AES256CBCDecrypt(const string & keyStr, const string & file) {
    ifstream in(file);
    if (in.is_open()) {
        int AES_BLOCK_SIZE = 16;
        vector<unsigned char> iv = randomIV(AES_BLOCK_SIZE);
        vector<unsigned char> cipher((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

        vector<unsigned char> key(keyStr.begin(), keyStr.end());

        AES aes(AESKeyLength::AES_256);
        vector<unsigned char> p = aes.DecryptCBC(cipher, key, iv);

        kunpad(p, AES_BLOCK_SIZE);
        ofstream out(file);
        out.write((char*)p.data(), p.size());
        out.close();
    }
    return false;
}

bool AES256ECBDecrypt(const string & keyStr, const string & file) {
    ifstream in(file);
    if (in.is_open()) {
        int AES_BLOCK_SIZE = 16;
        vector<unsigned char> cipher((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

        vector<unsigned char> key(keyStr.begin(), keyStr.end());

        AES aes(AESKeyLength::AES_256);
        vector<unsigned char> p = aes.DecryptECB(cipher, key);

        kunpad(p, AES_BLOCK_SIZE);
        ofstream out(file);
        out.write((char*)p.data(), p.size());
        out.close();
    }
    return false;
}

bool AES256ECBEncrypt(const string & keyStr, const string & file) {
    ifstream in(file);
    if (in.is_open()) {
        int AES_BLOCK_SIZE = 16;
        vector<unsigned char> plain((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        kpad(plain, AES_BLOCK_SIZE);
        vector<unsigned char> key(keyStr.begin(), keyStr.end());

        AES aes(AESKeyLength::AES_256);
        vector<unsigned char> c = aes.EncryptECB(plain, key);

        ofstream out(file);
        if (out.is_open()) {
            out.write(reinterpret_cast<char*>(c.data()), c.size());
            out.close();
        }
        return true;        
    }
    return false;
}

bool AES256CBCEncrypt(const string & keyStr, const string & file) {
    ifstream in(file);
    if (in.is_open()) {
        int AES_BLOCK_SIZE = 16;
        vector<unsigned char> iv = randomIV(AES_BLOCK_SIZE);
        vector<unsigned char> plain((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        kpad(plain, AES_BLOCK_SIZE);
        vector<unsigned char> key(keyStr.begin(), keyStr.end());

        AES aes(AESKeyLength::AES_256);
        vector<unsigned char> c = aes.EncryptCBC(plain, key, iv);

        ofstream out(file);
        if (out.is_open()) {
            out.write(reinterpret_cast<char*>(c.data()), c.size());
            out.close();
        }
        return true;        
    }
    return false;
}