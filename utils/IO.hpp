// input output header file

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstdlib>

using namespace std;
namespace fs = filesystem;

string EXCLUDE_FILES[] = {
    "kokosabzi"
};
int MAX_FILE_SIZE = 8388608; // maximum file size that can be encrypted (8MB)

bool isExcluded(const string & file) {
    for (const auto & exclude_file : EXCLUDE_FILES) {
        if (file.find(exclude_file) != string::npos) {
            return true;
        }
    }
    return false;
}

vector<string> getAllFiles(string path) {
    vector<string> files;
    for (const auto & entry : fs::directory_iterator(path)) {
        string path = entry.path().string();
        if (fs::is_directory(entry.status())) {
            vector<string> sub_files = getAllFiles(path);
            files.insert(files.end(), sub_files.begin(), sub_files.end());
        }
        else if (fs::is_regular_file(entry.status())) {
            if (isExcluded(path)) {
                continue;
            }
            else {
                // check if the file is too big
                if (fs::file_size(entry.path()) > MAX_FILE_SIZE) {
                    continue;
                }
                // check if the file is in the exclude list
                files.push_back(path);
            }
        }
    }
    return files;
}

inline static bool isFileExist(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}