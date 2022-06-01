#include <iostream>
#include "KeyUtil.hpp"

using namespace std;
using namespace KokoSabzi;

namespace KokoSabzi {
    void setup() {
        bool keyExist = KeyUtil::is_key_exist();
        if (keyExist)
            cout << "Hey" << endl;
        else
            cout << KeyUtil::generate_aes_256() << endl;
    }
}