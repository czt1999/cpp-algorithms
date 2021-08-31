//
// Created by ZiT on 2021/8/31.
//
#include <iostream>
#include <string>

using namespace std;

namespace cipher {

    namespace md5 {

        string hash(string &content) {

        }
    }
}

int main(int argc, char *argv[]) {
    string s = "If not me, who? If not now, when?";
    string h = cipher::md5::hash(s);
    cout << "hashes \"" << s << "\" via MD5 => " << h << endl;
}