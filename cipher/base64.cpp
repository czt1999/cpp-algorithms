//
// Created by ZiT on 2021/8/12.
//
#include <iostream>
#include <string>

using namespace std;

namespace cipher {

    /**
     * https://en.wikipedia.org/wiki/Base64
     */
    namespace base64 {

        const char characters[65] = {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '='
        };

        int indexOf(char c) {
            if (c >= 'A' && c <= 'Z') {
                return c - 'A';
            }
            if (c >= 'a' && c <= 'z') {
                return c - 'a' + 26;
            }
            if (c >= '0' && c <= '9') {
                return c - '0' + 52;
            }
            if (c == '+') {
                return 62;
            }
            if (c == '/') {
                return 63;
            }
            return c == '=' ? 64 : -1;
        }

        //
        // 1/2/3 bytes => 4 characters
        //
        string encodeBlock(byte *b, int n) {
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

        //
        // 4 characters => 1/2/3 bytes
        //
        string decodeBlock(string &s) {
            assert(4 == s.length());
            // 查找对应索引
            int indices[4] = {indexOf(s[0]), indexOf(s[1]),
                              indexOf(s[2]), indexOf(s[3])};
            int n = indices[3] == 64 ? (indices[2] == 64 ? 1 : 2) : 3;
            // 反推原始字节
            char bt[3];
            bt[0] = (indices[0] << 2) + (indices[1] >> 4);
            if (n == 1) {
                return {bt[0]};
            }
            bt[1] = (indices[1] << 4) + (indices[2] >> 2);
            if (n == 2) {
                return {bt[0], bt[1]};
            }
            bt[2] = (indices[2] << 6) + indices[3];
            return {bt[0], bt[1], bt[2]};
        }

        string encode(const string &s) {
            byte *bytes = (byte *) s.c_str();
            byte block[3];
            string enc;
            for (int i = 0; i < s.length(); i += 3) {
                int n = s.length() - i;
                if (n > 3) {
                    n = 3;
                }
                memcpy(block, (bytes + i), n);
                enc += encodeBlock(block, n);
            }
            return enc;
        }

        string decode(const string &s) {
            string dec;
            for (int i = 0; i < s.length(); i += 4) {
                string block_str = s.substr(i, 4);
                dec += decodeBlock(block_str);
            }
            return dec;
        }
    }
}

int main(int argc, char *argv[]) {
    string s = "Hello, my love.";
    string enc = cipher::base64::encode(s);
    cout << "encode \"" << s << "\" => " << enc << endl;
    string dec = cipher::base64::decode(enc);
    cout << "decode \"" << enc << "\" => " << dec << endl;
}