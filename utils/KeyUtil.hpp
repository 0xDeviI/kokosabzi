// a key generator and manager utility

#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>

using namespace std;

namespace KokoSabzi {

    const int aes256KeySize = 32;

    string randomAesKey(int size) {
        srand(time(0));
        char *buffer = new char[size];
        for (int i = 0; i < size; i++) {
            buffer[i] = (char) (rand() % (126 - 33 + 1) + 33);
        }
        string key = buffer;
        delete[] buffer;
        return key;
    }

    string generate_aes_256_key() {
        return randomAesKey(aes256KeySize);
    }
}