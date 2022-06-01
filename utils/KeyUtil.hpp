// a key generator and manager utility

#include <iostream>
#include <fstream>
#include <openssl/rand.h>
#include <openssl/aes.h>

using namespace std;

namespace KokoSabzi {
    class KeyUtil {
        public:
            static string generate_aes_256() {
                // generate a random key
                unsigned char key[32];
                RAND_bytes(key, sizeof(key));
                return "";
            }

            static bool is_key_exist() {
                return KeyUtil::is_file_exist("public.pub") && KeyUtil::is_file_exist("private.pem");
            }
            
            inline static bool is_file_exist(const string& name) {
                ifstream f(name.c_str());
                return f.good();
            }
    };
}