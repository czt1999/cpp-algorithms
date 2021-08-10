//
// Created by ZiT on 2021/8/7.
//
#include <array>
#include <string>
#include <vector>
#include <iostream>

#define MAX_CHILDREN 26

using namespace std;

namespace data_structure {

    namespace trie {

        typedef struct Node {
            char ch{0};
            array<struct Node *, MAX_CHILDREN> children{};
            int num{0}; // 以该节点的值为前缀的单词数量
            bool word{false};
        } *TNode;

        class Trie {
        private:
            TNode root{new Node};

            TNode search(const string &prefix);

            static void findWord(TNode node, const string &prefix, vector<string> &acc);

            static void removeNode(TNode node);

        public:
            // 加入单词
            bool add(const string &word);

            // 根据前缀统计单词数
            int countPrefix(string &prefix);

            // 根据前缀搜索单词
            vector<string> findWordByPrefix(const string &prefix);

            // 查找是否拥有某个单词
            bool hasWord(string &word);
        };

        //
        // ~~~~~~~~~~~~ Implements for Trie ~~~~~~~~~~~~
        //

        TNode Trie::search(const string &prefix) {
            TNode n = root;
            if (prefix.length()) {
                for (const auto &ch : prefix) {
                    if (!n) {
                        break;
                    }
                    n = n->children[ch - 'a'];
                }
            }
            return n;
        }

        void Trie::removeNode(TNode node) {
            if (node) {
                for_each(node->children.begin(), node->children.end(), removeNode);
                if (node->ch) { // 根节点不会被删除
                    delete node;
                }
            }
        }

        bool Trie::add(const string &word) {
            bool new_flag = false;
            if (word.length()) {
                TNode n = root;
                for (const auto &ch : word) {
                    n->num++;
                    TNode next = n->children[ch - 'a'];
                    if (!next) {
                        next = new Node;
                        next->ch = ch;
                    }
                    n = n->children[ch - 'a'] = next;
                }
                if (!n->word) {
                    new_flag = n->word = true;
                }
            }
            return new_flag;
        }

        int Trie::countPrefix(string &prefix) {
            TNode n = search(prefix);
            return n ? n->num : 0;
        }

        void Trie::findWord(TNode node, const string &prefix, vector<string> &acc) {
            if (node) {
                if (node->word && node->ch) {
                    acc.push_back(prefix);
                }
                for (int i = 0; i < MAX_CHILDREN; ++i) {
                    findWord(node->children[i], prefix + (char) ('a' + i), acc);
                }
            }
        }

        vector<string> Trie::findWordByPrefix(const string &prefix) {
            TNode n = search(prefix);
            vector<string> v{};
            findWord(n, prefix, v);
            return v;
        }

        bool Trie::hasWord(string &word) {
            TNode n = search(word);
            return n && n->word;
        }


    } // namespace trie
} // namespace data_structure

int main(int argc, char *argv[]) {
    data_structure::trie::Trie trie{};
    trie.add("apple");
    trie.add("and");
    trie.add("about");
    trie.add("alibaba");
    vector<string> v = trie.findWordByPrefix("a");
//    vector<string> v = trie.findWordByPrefix("an");
    for (const auto &s : v) {
        cout << s << endl;
    }
}