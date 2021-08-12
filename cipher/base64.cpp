//
// Created by ZiT on 2021/8/12.
//
#include <iostream>
#include <string>

using namespace std;

namespace cipher {

    namespace base64 {

        const char characters[65] = {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
                '='
        };

        string handleBlock(byte *b, int n) {
            int indices[4] = {64, 64, 64, 64};
            // 计算索引
            indices[0] = (int) (b[0] >> 2);
            indices[1] = (int) (b[0] << 6 >> 2);
            if (n > 1) {
                indices[1] += (int) (b[1] >> 4);
                indices[2] = (int) (b[1] << 4 >> 2);
                if (n == 3) {
                    indices[2] += (int) (b[2] >> 6);
                    indices[3] = (int) (b[2] << 2 >> 2);
                }
            }
            char ch[5];
            for (int i = 0; i < 4; ++i) {
                ch[i] = characters[indices[i]];
            }
            return {ch};
        }

        string encode(const string &s) {
            byte *bytes = (byte *) s.c_str();
            byte block[3];
            string enc;
            for (int i = 0; i < s.length(); i += 3) {
                int n = 3;
                if (n > s.length() - i) {
                    n = s.length() - i;
                }
                memcpy(block, (bytes + i), n);
                enc += handleBlock(block, n);
            }
            return enc;
        }

        string decode(const string &s) {

        }
    }
}

int main(int argc, char *argv[]) {
    cout << cipher::base64::encode("leasure.") << endl;
}